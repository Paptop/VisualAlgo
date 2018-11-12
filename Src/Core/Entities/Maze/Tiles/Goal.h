#pragma once

#include "Src/Core/Entities/Maze/Tiles/Tile.h"

namespace Vi
{
	class GoalTile : public Tile
	{
	public:
		GoalTile();
		~GoalTile();

		bool IsSolid() { return false; }
		bool IsGoal() { return true;  }
		float GetReward() { return 100.0f; }

		void Init();
		void Reset();

		void Update(float fDelta);
		void Render(Window* window);
	};
}