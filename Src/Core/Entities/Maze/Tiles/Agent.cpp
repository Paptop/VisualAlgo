#include "Src/Core/Entities/Maze/Tiles/Agent.h"
#include "Src/Core/Entities/Maze/Maze.h"
#include "Src/Vi/Global/Consts.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::Agent::Agent(Maze* maze)
: Tile()
, m_pcMaze(maze)
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(255, 0, 255));
	m_rect.setOutlineColor(sf::Color(255, 255, 0));
	m_rect.setOutlineThickness(5.f);
	m_rect.setPosition(0.0f, 0.0f);
	m_eCurrentRule = IDLE;
	m_vRules =
	{
//       U      R      D      L
		{0,-1}, {1,0}, {0,1}, {-1,0}
	};

	GOM.Add(this);
}

Vi::Agent::~Agent()
{
	GOM.Remove(this);
}

void Vi::Agent::Update(float fDelta)
{
	m_fProgress += fDelta;
	if (m_fProgress > 0.08f)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
		    m_eCurrentRule = UP;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			m_eCurrentRule = RIGHT;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			m_eCurrentRule = DOWN;
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			m_eCurrentRule = LEFT;
		}

		if (m_eCurrentRule != IDLE)
		{
			int newRow = m_pIndex.y + m_vRules[m_eCurrentRule].y;
			int newCol = m_pIndex.x + m_vRules[m_eCurrentRule].x;

			Tile* tile = m_pcMaze->GetTile(newRow, newCol);
			if (!tile)
			{
				m_eCurrentRule = IDLE;
				m_fProgress = 0.0f;
				return;
			}

			if (!tile->IsSolid())
			{
				sf::Vector2f pos = tile->GetPosition();

				m_pIndex.x = newCol;
				m_pIndex.y = newRow;

				m_rect.setPosition(pos);
			}

			m_eCurrentRule = IDLE;
		}
		m_fProgress = 0.0f;
	}
}

void Vi::Agent::Render(Window* window)
{
	window->Draw(m_rect);
}