#include "Src/Core/Entities/Maze/Maze.h"
#include "Src/Core/Entities/Maze/Tiles/Tiles.h"
#include "Src/Vi/Global/Consts.h"
#include "Src/Core/Entities/Maze/Camera.h"

#include <algorithm>
#include <iomanip>
#include <cassert>


Vi::Maze::Maze(std::string filename)
: m_filename(filename)
, m_agentX(0)
, m_agentY(0)
{
	InitMaze();
	InitObjects();
	m_pcCamera = new Camera(this);
	PrintToConsole();
	WaveAlgo();
}

void Vi::Maze::Init()
{
	InitMaze();
}

Vi::Maze::~Maze()
{
	for (int i = 0; i < (int)m_mazeGO.size(); ++i)
	{
		for (int j = 0; j < (int)m_mazeGO[i].size(); ++j)
		{
			delete m_mazeGO[i][j];
		}
	}

	delete m_pcCamera;
	delete[] m_F;
}

void Vi::Maze::InitMaze()
{
	m_input.open(m_filename);
	std::string line;

	if (m_input.is_open())
	{
		while (getline(m_input, line))
		{
			std::vector<int> row;

			for (int i = 0; i < (int)line.length(); ++i)
			{
				row.push_back(line[i] - '0');
			}

			m_maze.push_back(row);
		} //getline

	} // if open
	std::reverse(m_maze.begin(), m_maze.end());
	m_mazeW = m_maze[0].size();
	m_mazeH = m_maze.size();
	m_F = new sf::Vector2i[m_mazeH * m_mazeW];
}

void Vi::Maze::InitObjects()
{
	bool isAgent = false;

	for (int i = 0; i < (int)m_maze.size(); ++i)
	{
		std::vector<Tile*> tiles;
		for (int j = 0; j < (int)m_maze[i].size(); ++j)
		{
			int id = m_maze[i][j];
			if (id == 2)
			{
				isAgent = true;
				m_agentX = j;
				m_agentY = i;
				id = 0;
			}

			Tile* tile = CreateTile((Tiles)id, i, j);
			tile->SetPosition(m_maze.size() - i,j);
			tiles.push_back(tile);
		}
		m_mazeGO.push_back(tiles);
    }

	// Place agent on top
	if (isAgent)
	{
		int sizeY = m_mazeGO.size() - 1;
		Tile* tile = CreateTile(AGENT, m_agentY, m_agentX);
		float x = tile->GetSize().x * m_agentX + kfOffset;
		float y = tile->GetSize().y * (m_maze.size() - m_agentY) + kfOffset;
		tile->SetPosition(Vector2(x, y));
		m_mazeGO[sizeY].push_back(tile);
	}
}


void Vi::Maze::PrintToConsole()
{
	if (m_maze.size() == 0)
	{
		return;
	}

	std::cout << "Y" << std::endl;
	int size = (int)m_maze[0].size();

	for (int i = (int)m_maze.size() - 1; i >= 0; --i)
	{
		std::cout << " " << std::setfill(' ') << std::setw(3) << i + 1 << " | ";
		for (int c : m_maze[i])
		{
			std::cout << std::setfill(' ') << std::setw(4) << c;
		}

		std::cout << std::endl;
	}

	std::cout << "       ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << "----";
	}
	std::cout << "> X";
	std::cout << std::endl;

	std::cout << "       ";
	for (int i = 0; i < size; ++i)
	{
		std::cout << std::setfill(' ') << std::setw(4) << i;
	}
	std::cout << std::endl;
}


Vi::Tile* Vi::Maze::CreateTile(Tiles id, int i, int j)
{
	Tile* tile = nullptr;
	switch (id)
	{
		case SIMPLE_TILE:
			tile = new SimpleTile();
			break;
		case WALL_TILE:
			tile = new Wall();
			break;
		case AGENT:
			tile = new Agent(this);
			break;
		case GOAL:
			tile = new GoalTile();
			break;
		default:
			assert(false);
	}

	tile->SetIndex(i, j);

	return tile;
}


Vi::Tile* Vi::Maze::GetTile(int row, int col)
{
	if (row >= static_cast<int>(m_mazeGO.size()) || row < 0)
	{
		return nullptr;
	}

	if(col >= static_cast<int>(m_mazeGO[row].size()) || col < 0)
	{
		return nullptr;
	}

	return m_mazeGO[row][col];
}

void Vi::Maze::SetOffset(float fOffsetX, float fOffsetY)
{
	for (int i = 0; i < (int)m_mazeGO.size(); ++i)
	{
		for (int j = 0; j < (int)m_mazeGO[i].size(); ++j)
		{
			m_mazeGO[i][j]->SetOffset(fOffsetX, fOffsetY);
		}
	}
}

void Vi::Maze::WaveAlgo()
{
	bool Yes = false;
	CLOSE = 0;
	NEWN = 0;
	m_F[0] = sf::Vector2i(m_agentX,m_agentY);
	m_rules = { {-1, 0}, {0, -1}, {1, 0}, {0,1} };
	do
	{
		int X = m_F[CLOSE].x;
		int Y = m_F[CLOSE].y;
		int K = 0;
		do
		{
			int U = X + m_rules[K].x;
			int V = Y + m_rules[K].y;
			

			if (m_mazeGO[V][U]->GetId() == 0)
			{
				int PrevId = m_mazeGO[Y][X]->GetId();
				m_mazeGO[V][U]->SetId(PrevId + 1);
				if (U == 0 || U == m_mazeW - 1 || V == 0 || V == m_mazeH - 1)
				{
					Yes = true;
				}
				else
				{
					m_F[NEWN] = sf::Vector2i(U, V);
					NEWN = NEWN + 1;
				}

			}

			K++;

		} while (K < 3 && !Yes);

		CLOSE++;
	}
	while (!Yes && CLOSE <= NEWN);
}