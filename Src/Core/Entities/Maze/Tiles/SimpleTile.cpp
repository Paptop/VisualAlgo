#include "Src/Core/Entities/Maze/Tiles/SimpleTile.h"
#include "Src/Vi/Sys/GoManager.h"

#define WIDTH 40
#define HEIGHT 40

Vi::SimpleTile::SimpleTile()
{
	Init();
	m_rect.setPosition(0.0f, 0.0f);
	GOM.AddFront(this);
}

void Vi::SimpleTile::Reset()
{
	Init();
}

void Vi::SimpleTile::Init()
{
	m_rect.setSize(sf::Vector2f(WIDTH, HEIGHT));
	m_rect.setFillColor(sf::Color(255, 255, 255));
	m_rect.setOutlineColor(sf::Color(252, 84, 84));
	m_rect.setOutlineThickness(5.f);
	m_text.setString("0");
	m_isLabelHidden = true;
	m_id = 0;
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
	if (m_rect.getPosition().x > -WIDTH && m_rect.getPosition().x <= iPxWidth &&
		m_rect.getPosition().y > -HEIGHT && m_rect.getPosition().y <= iPxHeight)
	{
		window->Draw(m_rect);

		if (!m_isLabelHidden)
		{
			window->Draw(m_text);
		}
	}
}