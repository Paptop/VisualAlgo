#pragma once
#include "Src/Core/Entities/Maze/Maze.h"

#include "Src/Vi/GO/GameObject.h"
#include "Src/Core/GUI/Dummy.h"

namespace Vi
{

	class Camera : public GameObject
	{
	public:

		enum ECamera
		{
			MOVE_UP,
			MOVE_RIGHT,
			MOVE_DOWN,
			MOVE_LEFT,
			IDLE
		};

		Camera(Maze* maze);
		~Camera();

		void Update(float fDelta);
		void Render(Window* window);

		void InitButtons();
	private:
		std::vector<Vector2> m_dir;
		std::vector<Dummy*> m_buttons;
		Maze* m_pcMaze;
		ECamera m_currentDirection;
		float m_fProgress;
		float m_fSpeed;
	};

};