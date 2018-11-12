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
		float GetReward() { return 0.0f; }
		bool IsGoal() { return false; }

		void Update(float fDelta);
		void Render(Window* window);
		void Reset();
		void Init();


		sf::Vector2i ApplyRule(RULES rule);
		bool MoveAgent(RULES rule);
		float GetActionReward(RULES rule);
		std::vector<float> GetCurrentQValues();
		std::vector<float> GetNextQValues(int row, int col);

	private:
		std::vector< sf::Vector2i >			m_vRules;
		RULES								m_eCurrentRule;
		Maze*								m_pcMaze;
		float								m_fProgress;
	};
}

#endif