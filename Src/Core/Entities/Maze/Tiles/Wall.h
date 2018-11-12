#ifndef WALL_H
#define WALL_H

#include "Src/Core/Entities/Maze/Tiles/Tile.h"

namespace Vi
{
	class Wall : public Tile
	{
	public:
		Wall();
		~Wall();

		bool IsSolid() { return true; }
		bool IsGoal() { return false; }
		float GetReward() { return -10.0; }

		void Reset();
		void Init();
		void Update(float fDelta);
		void Render(Window* window);
	};
}


#endif