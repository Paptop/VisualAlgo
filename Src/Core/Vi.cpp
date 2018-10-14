#include "Src/Core/Vi.h"

#include "Src/Vi/Sys/GoManager.h"
#include "Src/Vi/Sys/Window.h"

#include "Src/Core/Entities/Maze/Maze.h"

Vi::ViAl::ViAl()
{
	m_pcWindow = new Window();
}

Vi::ViAl::~ViAl()
{
	delete m_pcWindow;
	delete m_pcModel;
}

void Vi::ViAl::Start()
{
	m_bIsRunning = true;
	Init();
	Loop();
}

void Vi::ViAl::Init()
{
	m_pcModel = new Maze("Maze.txt");

}

void Vi::ViAl::Loop()
{
	sf::Clock clock;
	float lastTime = clock.getElapsedTime().asSeconds();
	while (m_bIsRunning)
	{
		sf::Event event;
		while (m_pcWindow->PollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_pcWindow->Close();
				m_bIsRunning = false;
			}
		}

		float current = clock.getElapsedTime().asSeconds();
		float delta = current - lastTime;
		float fps = 1.f / delta;
		std::cout << "Fps : " << fps << std::endl;
		GOM.Update(delta);
		m_pcWindow->Clear();
		GOM.Render(m_pcWindow);
		m_pcWindow->Diplay();

		lastTime = current;
	}
}