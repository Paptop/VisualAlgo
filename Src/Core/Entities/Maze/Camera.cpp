#include "Src/Core/Entities/Maze/Camera.h"
#include <functional>
#include "Src/Vi/Sys/GoManager.h"

Vi::Camera::Camera(Maze* maze)
	: m_pcMaze(maze)
	, m_fProgress(0.0f)
	, m_fSpeed(1000.f)
	, m_currentDirection(IDLE)
{
	m_dir = {
		{ 0.0f, -m_fSpeed},
		{ m_fSpeed, 0.0f },
		{ 0.0f, m_fSpeed},
		{ -m_fSpeed, 0.0f}
	};

	InitButtons();
	GOM.Add(this);
}

void Vi::Camera::InitButtons()
{
	m_buttons.push_back(new Dummy(std::bind(&Vi::Maze::PrintToConsole, m_pcMaze), "PrintMaze", 0));
	m_buttons.push_back(new Dummy(std::bind(&Vi::Maze::WaveAlgo, m_pcMaze), "Wave", 1));
	m_buttons.push_back(new Dummy(std::bind(&Vi::Maze::GenMaze, m_pcMaze), "GenMaze", 2));
}

Vi::Camera::~Camera()
{
	for (Dummy* d : m_buttons)
	{
		delete d;
	}

	GOM.Remove(this);
}

void Vi::Camera::Update(float fDeltaTime)
{
	m_fProgress += fDeltaTime;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		m_currentDirection = MOVE_UP;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_currentDirection = MOVE_RIGHT;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		m_currentDirection = MOVE_DOWN;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_currentDirection = MOVE_LEFT;
	}
		
	if (m_currentDirection != IDLE)
	{
		Vector2 offset = m_dir[m_currentDirection];
		m_pcMaze->SetOffset(offset.m_x * fDeltaTime, offset.m_y * fDeltaTime);
	}

	m_currentDirection = IDLE;
	m_fProgress = 0.0f;
}

void Vi::Camera::Render(Window* m_pcWindow)
{
	for (Dummy* d : m_buttons)
	{
		d->Render(m_pcWindow);
	}
}
