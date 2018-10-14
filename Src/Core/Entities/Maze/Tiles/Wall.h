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
		int GetReward() { return 0; }

		void Reset();
		void Init();
		void Update(float fDelta);
		void Render(Window* window);
	};
}


#endif