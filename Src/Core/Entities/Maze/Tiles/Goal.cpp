#include "Src/Core/Entities/Maze/Tiles/Goal.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::GoalTile::GoalTile()
{
	Init();
	m_rect.setPosition(0.0f, 0.0f);
	GOM.AddFront(this);
}

Vi::GoalTile::~GoalTile()
{
	GOM.Remove(this);
}

void Vi::GoalTile::Update(float fDelta)
{

}

void Vi::GoalTile::Reset()
{
	Init();
}

void Vi::GoalTile::Init()
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(255, 255, 0));
	m_rect.setOutlineColor(sf::Color(252, 84, 84));
	m_rect.setOutlineThickness(5.f);
	m_id = 0;
}

void Vi::GoalTile::Render(Window* window)
{
	window->Draw(m_rect);
}