#include "Src/Core/Entities/Maze/Tiles/SimpleTile.h"
#include "Src/Vi/Sys/GoManager.h"

Vi::SimpleTile::SimpleTile()
{
	m_rect.setSize(sf::Vector2f(40, 40));
	m_rect.setFillColor(sf::Color(255, 255, 255));
	m_rect.setOutlineColor(sf::Color(252, 84, 84));
	m_rect.setOutlineThickness(5.f);
	m_rect.setPosition(0.0f, 0.0f);
	m_text.setString("0");
	m_id = 0;
	GOM.Add(this);
}

Vi::SimpleTile::~SimpleTile()
{
	GOM.Remove(this);
}

void Vi::SimpleTile::Update(float fDelta)
{
}

void Vi::SimpleTile::Render(Window* window)
{
	window->Draw(m_rect);

	if (!m_isLabelHidden)
	{
		window->Draw(m_text);
	}
}