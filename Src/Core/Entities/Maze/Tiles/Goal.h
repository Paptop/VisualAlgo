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
		int GetReward() { return 0; }

		void Update(float fDelta);
		void Render(Window* window);
	};
}