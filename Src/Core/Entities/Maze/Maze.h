#pragma once

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <fstream>
#include "Src/Core/Model.h"
#include "SFML/System/Vector2.hpp"

namespace Vi
{

	class Tile;
	class Camera;

	class Maze : public Model
	{
	public:

		enum Tiles
		{
			SIMPLE_TILE = 0,
			WALL_TILE = 1,
			AGENT = 2,
			GOAL = 3
		};

		void Update(float fDelta);
	
		Maze(std::string fileName);
		~Maze();
		void PrintToConsole();
		void Init();
		void SetOffset(float fOffsetX, float fOffsetY);
		void Reset();
		void PlaceAgent(int row, int col);
		void GenMaze();
		Tile* GetTile(int row, int col);


////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////
		void WaveAlgo();
		void Back(int U, int V);
	private:
		void GenM(int x, int y);
		void InitMaze();
		void InitObjects();
		// TODO: create factory
		Tile* CreateTile(Tiles id, int i, int j);
	private:
		std::vector< std::vector<int> > m_maze;
		std::vector< std::vector<Tile*> > m_mazeGO;
		std::vector< std::vector<Tile*> > m_anim;

		Camera* m_pcCamera;
		std::ifstream m_input;
		std::string m_filename;

		int m_agentY;
		int m_agentX;
///////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////
		sf::Vector2i* m_F;
		std::vector< sf::Vector2i > m_rules;
		std::vector<Tile*> m_path;
		std::ofstream m_output;
		//Path
		std::vector<int> m_R;

		std::vector< sf::Vector2i > m_nodes;
		int m_mazeW;
		int m_mazeH;
		int CLOSE;
		int NEWN;

		float m_fProgress;
		float m_fDelay;

		int r, g, b;
	};
}
