#include "Src/Core/Entities/Maze/Tiles/Wall.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::Wall::Wall()
{
	Init();
	m_rect.setPosition(0.0f, 0.0f);
	GOM.AddFront(this);
}

Vi::Wall::~Wall()
{
	GOM.Remove(this);
}

void Vi::Wall::Update(float fDelta)
{

}

void Vi::Wall::Render(Window* window)
{
	if (m_rect.getPosition().x > -40 && m_rect.getPosition().x <= iPxWidth &&
		m_rect.getPosition().y > -40 && m_rect.getPosition().y <= iPxHeight)
	{
		window->Draw(m_rect);
		window->Draw(m_text);
	}
}

void Vi::Wall::Reset()
{
	Init();
}

void Vi::Wall::Init()
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(0, 0, 0));
	m_rect.setOutlineColor(sf::Color(252, 84, 84));
	m_rect.setOutlineThickness(5.f);
	m_text.setString("1");
	m_id = 1;
}