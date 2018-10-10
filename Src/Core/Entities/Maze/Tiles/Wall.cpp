#include "Src/Core/Entities/Maze/Tiles/Wall.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::Wall::Wall()
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(0, 0, 0));
	m_rect.setOutlineColor(sf::Color(252, 84, 84));
	m_rect.setOutlineThickness(5.f);
	m_rect.setPosition(0.0f, 0.0f);
	m_text.setString("1");
	m_id = 1;
	GOM.Add(this);
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
	window->Draw(m_rect);
	window->Draw(m_text);
}