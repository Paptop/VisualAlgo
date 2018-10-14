#ifndef AGENT_H
#define AGENT_H

#include "Src/Core/Entities/Maze/Tiles/Tile.h"

namespace Vi
{
	class Maze;

	class Agent : public Tile
	{
	public:
		
		enum RULES
		{
			UP,
			RIGHT,
			DOWN,
			LEFT,
			IDLE,
			PLACE,
			COUNT
		};

		Agent(Maze* maze);
		~Agent();

		bool IsSolid() { return false; }
		int GetReward() { return 0; }

		void Update(float fDelta);
		void Render(Window* window);
		void Reset();
		void Init();

	private:
		std::vector< sf::Vector2i > m_vRules;
		RULES						m_eCurrentRule;
		Maze*						m_pcMaze;
		float						m_fProgress;
	};
}

#endif