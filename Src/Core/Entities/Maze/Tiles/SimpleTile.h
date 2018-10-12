#ifndef SIMPLETILE_H
#define SIMPLETILE_H

#include "Src/Core/Entities/Maze/Tiles/Tile.h"

namespace Vi
{
	class SimpleTile : public Tile
	{
	public:
		SimpleTile();
		~SimpleTile();

		bool IsSolid() { return false; }
		int GetReward() { return 0; }

		void Update(float fDelta);
		void Render(Window* window);
	private:
		float fProgress;
		float fDelay;
	};
}

#endif