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
		bool IsGoal() { return false; }
		float GetReward() { return -1.0f; }

		void Init();
		void Reset();
		void Update(float fDelta);
		void Render(Window* window);
	private:
		float fProgress;
		float fDelay;
	};
}

#endif