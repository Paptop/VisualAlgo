#include "Src/Core/Entities/Maze/Tiles/Agent.h"
#include "Src/Core/Entities/Maze/Maze.h"
#include "Src/Vi/Global/Consts.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::Agent::Agent(Maze* maze)
: Tile()
, m_pcMaze(maze)
, m_fProgress(0.0f)
{
	Init();
	m_rect.setPosition(0.0f, 0.0f);
	GOM.Add(this);
}

Vi::Agent::~Agent()
{
	GOM.Remove(this);
}

bool Vi::Agent::MoveAgent(RULES rule)
{
	int newRow = m_pIndex.y + m_vRules[rule].y;
	int newCol = m_pIndex.x + m_vRules[rule].x;

	Tile* tile = m_pcMaze->GetTile(newRow, newCol);
	if (!tile)
	{
		return false;
	}

	if (!tile->IsSolid())
	{
		sf::Vector2f pos = tile->GetPosition();

		m_pIndex.x = newCol;
		m_pIndex.y = newRow;

		m_rect.setPosition(pos);
		m_text.setPosition(pos);

		if (tile->IsGoal())
		{
			return true;
		}
	}

	return false;
}

float Vi::Agent::GetActionReward(RULES rule)
{
	int newRow = m_pIndex.y + m_vRules[rule].y;
	int newCol = m_pIndex.x + m_vRules[rule].x;

	Tile* tile = m_pcMaze->GetTile(newRow, newCol);
	if (tile)
	{
		return tile->GetReward();
	}
	else
	{
		return -100.0f;
	}
}


std::vector<float> Vi::Agent::GetCurrentQValues()
{
	return GetNextQValues(m_pIndex.x, m_pIndex.y);
}

sf::Vector2i Vi::Agent::ApplyRule(RULES rule)
{
	sf::Vector2i res;
	res.y = m_pIndex.y + m_vRules[rule].y;
	res.x = m_pIndex.x + m_vRules[rule].x;
	return res;
}

std::vector<float> Vi::Agent::GetNextQValues(int row, int col)
{
	std::vector<float> QRow;

	for (int i = 0; i < m_vRules.size(); ++i)
	{
		int newRow = row + m_vRules[i].y;
		int newCol = col + m_vRules[i].x;

		Tile* tile = m_pcMaze->GetTile(newRow, newCol);
		if (tile)
		{
			QRow.push_back(tile->GetQValue());
		}
		else
		{
			// Punish agent OOB
			QRow.push_back(-100.0f);
		}
	}

	return QRow;
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
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
		{
			m_eCurrentRule = PLACE;
		}

		if (m_eCurrentRule != IDLE && m_eCurrentRule != PLACE)
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
				m_text.setPosition(pos);
			}

			m_eCurrentRule = IDLE;
		}
		else if (m_eCurrentRule == PLACE)
		{
			m_pcMaze->PlaceAgent(m_pIndex.y, m_pIndex.x);
		}
		m_fProgress = 0.0f;
	}
}

void Vi::Agent::Render(Window* window)
{
	window->Draw(m_rect);
	window->Draw(m_text);
}


void Vi::Agent::Reset()
{
	Init();
}

void Vi::Agent::Init()
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(255, 0, 255));
	m_rect.setOutlineColor(sf::Color(255, 255, 0));
	m_rect.setOutlineThickness(5.f);
	m_text.setString("2");
	m_id = 2;

	m_eCurrentRule = IDLE;
	m_vRules =
	{
	   //       U      R      D      L
	   {0,1}, {1,0}, {0,-1}, {-1,0}
	};

}