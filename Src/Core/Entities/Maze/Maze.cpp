#include "Src/Core/Entities/Maze/Maze.h"
#include "Src/Core/Entities/Maze/Tiles/Tiles.h"
#include "Src/Vi/Global/Consts.h"
#include "Src/Core/Entities/Maze/Camera.h"
#include "Src/Vi/Sys/GoManager.h"

#include "SFML/Main.hpp"
#include <algorithm>
#include <iomanip>
#include <cassert>
#include <stdlib.h>  
#include <random>
#include <functional>


Vi::Maze::Maze(std::string filename)
: m_filename(filename)
, m_agentX(0)
, m_agentY(0)
, m_fProgress(0)
, m_fDelay(0)
{
	m_output.open("OUTPUT.TXT");
	GOM.Add(this);

	InitMaze();
	InitObjects();
	m_pcCamera = new Camera(this);
	std::cout << " Part 1 : Data" << std::endl << std::endl;
	std::cout << "  1.1 Maze" << std::endl << std::endl;
	PrintToConsole();
	std::cout << std::endl;
	std::cout << "  1.2 Initial position X=" << m_agentX << " , Y=" << m_agentY << ". L=2" << std::endl << std::endl;
	std::cout << " Part 2 is located OUTPUT.TXT" << std::endl << std::endl;
	std::cout << " Part 3 " << std::endl << std::endl;
	std::cout << "  3.3 Rules: ";
	for (int i = 0; i < m_R.size(); ++i)
	{
		std::cout << "R" << m_R[i] << " ";
	}
	std::cout << std::endl << std::endl;
	std::cout << "  3.4 Nodes: ";
	for (int i = 0; i < m_nodes.size(); ++i)
	{
		std::cout << "[x=" << m_nodes[i].x + 1 << ", y=" << m_nodes[i].y + 1 << "]" << " ";
	}

}

void Vi::Maze::Reset()
{
	m_anim.clear();

	for (int i = 0; i < (int)m_maze.size(); ++i)
	{
		for (int j = 0; j < (int)m_maze[i].size(); ++j)
		{
			m_mazeGO[i][j]->Reset();
		}
	}
	m_mazeGO[m_agentY][m_agentX]->SetId(2);
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

	}
	else
	{
		GenM(30, 35);
	}
	std::reverse(m_maze.begin(), m_maze.end());
	m_mazeW = m_maze[0].size();
	m_mazeH = m_maze.size();
	m_F = new sf::Vector2i[m_mazeH * m_mazeW];
}

void Vi::Maze::PlaceAgent(int row, int col)
{
	m_agentX = col;
	m_agentY = row;
	m_maze[row][col] = 2;
	m_mazeGO[row][col]->SetId(2);
}

void Vi::Maze::GenM(int row, int col)
{
	std::random_device r;
	std::default_random_engine generator(r());
	std::uniform_int_distribution<int> distribution(1, 6);

	std::vector<int> firstRow;

	auto dice = std::bind(distribution, generator);

	for (int i = 0; i < col; ++i)
	{
		firstRow.push_back(1);
	}

	for (int i = 0; i < col; ++i)
	{
		int goal = dice();
		if (goal == 6)
		{
			firstRow[i] = 0;
		}
	}

	m_maze.push_back(firstRow);

	for (int j = 1; j < row; ++j)
	{
		std::vector<int> y;
		for (int i = 0; i < col; ++i)
		{
			int obs = dice();
			if (obs <= 2)
			{
				y.push_back(1);
			}
			else
			{
				y.push_back(0);
			}
		}
		y[0] = 1;
		y[y.size() - 1] = 1;
		m_maze.push_back(y);
	}

	for (int i = 0; i < col; ++i)
	{
		m_maze[m_maze.size() - 1][i] = 1;
	}

	int agentX = dice() % (col - 2) + 1;
	int agentY = dice() % (row - 1) + (row / 2 - 1);
	m_maze[agentY][agentX] = 2;

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
		m_mazeGO[m_agentY][m_agentX]->SetId(2);
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
		std::cout << std::setfill(' ') << std::setw(4) << i + 1;
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
			m_goal = tile;
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
	Reset();
	bool Yes = false;
	CLOSE = 0;
	NEWN = 0;
	m_F[0] = sf::Vector2i(m_agentX,m_agentY);
	m_rules = { {-1, 0}, {0, -1}, {1, 0}, {0,1} };
	unsigned int waveCount = 0;
	unsigned int waveLabel = 0;
	int closePrev = -1;
	int U = 0;
	int V = 0;
	r = 235, g = 55, b = 55;
	m_output << "WAVE " << waveCount << ", label L=" << "\"" << 2 << "\"" << ". Initial position X=" << m_agentX+1 << ", Y=" << m_agentY+1 << ", NEWN=" << NEWN + 1 << std::endl;
	m_output << std::endl;

	do
	{
		int X = m_F[CLOSE].x;
		int Y = m_F[CLOSE].y;
		int K = 0;

		do
		{

			U = X + m_rules[K].x;
			V = Y + m_rules[K].y;

			int id = m_mazeGO[Y][X]->GetId();

			if (m_mazeGO[Y][X]->GetId() != waveLabel)
			{
				m_output << "WAVE " << ++waveCount << ", label L=" << "\"" << id+1 << "\"" << std::endl;
				m_anim.push_back(std::vector<Tile*>());
			}
			waveLabel = id;

			if (closePrev != CLOSE)
			{
				m_output << std::setfill(' ') << std::setw(5) << "	Close " << "Close=" << CLOSE + 1 << ", X=" << X + 1 << ", Y=" << Y + 1 << "." << std::endl;
			}
			closePrev = CLOSE;

			if (m_mazeGO[V][U]->GetId() > 1)
			{
				m_output << std::setfill(' ') << std::setw(5) << "		R" << K + 1 << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " CLOSED or OPEN." << std::endl;
			}

			if (m_mazeGO[V][U]->GetId() == 0)
			{
				int PrevId = m_mazeGO[Y][X]->GetId();
				m_mazeGO[V][U]->SetId(PrevId + 1);
				//m_mazeGO[V][U]->SetColor(215, 115, 115, 255)

				m_anim.back().push_back(m_mazeGO[V][U]);
				waveLabel = PrevId;

				if (U == 0 || U == m_mazeW - 1 || V == 0 || V == m_mazeH - 1)
				{
					Yes = true;
				}

				else
				{
					NEWN = NEWN + 1;
					m_output << std::setfill(' ') << std::setw(5) << "		R" << K + 1 << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " Free. NEWN=" << NEWN + 1 << "." << std::endl;
					m_F[NEWN] = sf::Vector2i(U, V);
				}

			}

			if (m_mazeGO[V][U]->GetId() == 1)
			{
				m_output << std::setfill(' ') << std::setw(5) << "		R" << K+1 << ". X=" << U+1 << ", Y=" << V+1 << "." << " Wall." << std::endl;
			}
			K++;

		} while (K <= 3 && !Yes);

		if (Yes)
		{
			m_output << std::setfill(' ') << std::setw(5) << "		R" << K << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " Free. NEWN=" << NEWN + 2 << "." << " Terminal." << std::endl;
		}
		m_output << std::endl;
		CLOSE++;

		
	}
	while (!Yes && CLOSE <= NEWN);

	if (Yes)
	{
		Back(U, V);
	}

	std::reverse(m_anim.begin(), m_anim.end());
	//std::reverse(m_path.begin(), m_path.end());
}


void Vi::Maze::Back(int U, int V)
{
	int VV = 0;
	int UU = 0;
	int r = 0, g = 128, b = 255, a = 255;
	m_mazeGO[V][U]->SetColor(r, g, b, a);
	m_nodes.push_back(sf::Vector2i(U, V));
	m_path.push_back(m_mazeGO[V][U]);

	int flipedRules[] = { 3, 4, 1, 2 };

	while (m_mazeGO[V][U]->GetId() != 2)
	{
		for (int i = 0; i < m_rules.size(); ++i)
		{
			UU = U + m_rules[i].x;
			VV = V + m_rules[i].y;

			if (UU >= 0 && UU < m_mazeW && VV >= 0 && VV < m_mazeH)
			{
				int newId = m_mazeGO[VV][UU]->GetId();
				int oldId = m_mazeGO[V][U]->GetId();
				if (newId == oldId - 1)
				{
					m_R.push_back(flipedRules[i]);
					m_nodes.push_back(sf::Vector2i(UU, VV));
					//m_mazeGO[VV][UU]->SetColor(r, g, b, a);
					m_path.push_back(m_mazeGO[VV][UU]);
					U = UU;
					V = VV;
					break;
				}
			}
		}
	}

	std::reverse(m_nodes.begin(), m_nodes.end());
	std::reverse(m_R.begin(), m_R.end());
}


void Vi::Maze::Update(float fDelta)
{

	if (m_anim.size() > 0)
	{
		m_fDelay += fDelta;

		if (m_fDelay > 0.05f)
		{
			m_fProgress += fDelta * 3.0f;
			float modProg = sinf(3.14159 * 0.5 * m_fProgress);

			if (m_fProgress > 0.6f)
			{

				// finish
				for (Tile* tile : m_anim.back())
				{
					tile->SetAlfa(r, g, b, modProg);
					tile->SetLabelHidden(false);
				}
				m_anim.pop_back();
				if (r > 100)
				{
					r -= 10;
					b += 10;
				}
				m_fProgress = 0.0f;
				m_fDelay = 0.0f;
			}
			else
			{
				for (Tile* tile : m_anim.back())
				{
					tile->SetAlfa(r, g, b, modProg);
				}
			}
		}
	}
	else
	{
		if (m_path.size() > 0)
		{
			m_fDelay += fDelta;

			if (m_fDelay > 0.5f)
			{
				m_path.back()->SetColor(255, 250, 0, 255);
				m_path.pop_back();
				m_fDelay = 0.0f;
			}
		}
	}
}

void Vi::Maze::GenMaze()
{
	delete[] m_F;
	m_maze.clear();
	GenM(200, 150);

	for (int i = 0; i < (int)m_mazeGO.size(); ++i)
	{
		for (int j = 0; j < (int)m_mazeGO[i].size(); ++j)
		{
			delete m_mazeGO[i][j];
		}
	}

	m_mazeGO.clear();
	InitObjects();
}


void Vi::Maze::Astar()
{
	Reset();
	bool Yes = false;
	CLOSE = 0;
	NEWN = 0;
	m_F[0] = sf::Vector2i(m_agentX, m_agentY);
	m_rules = { {-1, 0}, {0, -1}, {1, 0}, {0,1} };
	unsigned int waveCount = 0;
	unsigned int waveLabel = 0;
	int closePrev = -1;
	int U = 0;
	int V = 0;
	r = 235, g = 55, b = 55;
	m_output << "WAVE " << waveCount << ", label L=" << "\"" << 2 << "\"" << ". Initial position X=" << m_agentX + 1 << ", Y=" << m_agentY + 1 << ", NEWN=" << NEWN + 1 << std::endl;
	m_output << std::endl;

	std::multimap<float, sf::Vector2i> queue;
	std::multimap<float, sf::Vector2i> closeQueue;
	queue.insert({ 0, sf::Vector2i(m_agentX, m_agentY) });
	do
	{
		int X = queue.begin()->second.x;
		int Y = queue.begin()->second.y;
		int K = 0;

		
		for (auto p : queue)
		{
			std::cout << "First ->" << p.first << " Second -> " << " X : " << p.second.x << " Y : " << p.second.y << " Goal -> " << m_goal->GetId() << std::endl;
		}

		do
		{
			U = X + m_rules[K].x;
			V = Y + m_rules[K].y;

			int id = m_mazeGO[Y][X]->GetId();
			
			if (id == 8)
			{
				std::cout << " ID " << id << std::endl;
			}

			if (m_mazeGO[Y][X]->GetId() != waveLabel)
			{
				m_output << "WAVE " << ++waveCount << ", label L=" << "\"" << id + 1 << "\"" << std::endl;
				m_anim.push_back(std::vector<Tile*>());
			}
			waveLabel = id;

			if (closePrev != CLOSE)
			{
				m_output << std::setfill(' ') << std::setw(5) << "	Close " << "Close=" << CLOSE + 1 << ", X=" << X + 1 << ", Y=" << Y + 1 << "." << std::endl;
			}
			closePrev = CLOSE;

			if (m_mazeGO[V][U]->GetId() > 1)
			{
				m_output << std::setfill(' ') << std::setw(5) << "		R" << K + 1 << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " CLOSED or OPEN." << std::endl;
			}

			if (m_mazeGO[V][U]->GetId() == 0)
			{
				int PrevId = m_mazeGO[Y][X]->GetId();
				m_mazeGO[V][U]->SetId(PrevId + 1);
				//m_mazeGO[V][U]->SetColor(215, 115, 115, 255)

				m_anim.back().push_back(m_mazeGO[V][U]);
				waveLabel = PrevId;

				if (U == 0 || U == m_mazeW - 1 || V == 0 || V == m_mazeH - 1)
				{
					Yes = true;
				}
				else
				{
					NEWN = NEWN + 1;
					m_output << std::setfill(' ') << std::setw(5) << "		R" << K + 1 << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " Free. NEWN=" << NEWN + 1 << "." << std::endl;
					//m_F[NEWN] = sf::Vector2i(U, V);
					float dist = m_mazeGO[V][U]->GetDistance(*m_goal);
					//std::cout << dist << std::endl;
					closeQueue.insert({ dist,sf::Vector2i(U,V) });
				}

			}

			if (m_mazeGO[V][U]->GetId() == 1)
			{
				m_output << std::setfill(' ') << std::setw(5) << "		R" << K + 1 << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " Wall." << std::endl;
			}



			K++;

		} while (K <= 3 && !Yes);

		if (Yes)
		{
			m_output << std::setfill(' ') << std::setw(5) << "		R" << K << ". X=" << U + 1 << ", Y=" << V + 1 << "." << " Free. NEWN=" << NEWN + 2 << "." << " Terminal." << std::endl;
			break;
		}
		m_output << std::endl;

		if (closeQueue.size() == 0)
		{
			break;
		}

		if (queue.begin() != queue.end())
		{
			//queue.clear();
			queue.erase(queue.begin());
			queue.insert(*closeQueue.begin());
			closeQueue.erase(closeQueue.begin());
		}
		//CLOSE++;

	} while (!Yes && queue.size() > 0);

	if (Yes)
	{
		Back(U, V);
	}

	std::reverse(m_anim.begin(), m_anim.end());
	//std::reverse(m_path.begin(), m_path.end());
}