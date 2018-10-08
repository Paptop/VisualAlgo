#include "Window.h"

#include "Src/Vi/Global/Consts.h"

Vi::Window::Window()
{
	m_pcWindow = new sf::RenderWindow(sf::VideoMode(iPxWidth, iPxHeight), "VI");
}

Vi::Window::~Window()
{
	delete m_pcWindow;
}

bool Vi::Window::IsOpen() const
{
	return m_pcWindow->isOpen();
}

void Vi::Window::Close()
{
	m_pcWindow->close();
}

bool Vi::Window::PollEvent(sf::Event& event)
{
	return m_pcWindow->pollEvent(event);
}

void Vi::Window::Clear()
{
	m_pcWindow->clear();
}

void Vi::Window::Diplay()
{
	m_pcWindow->display();
}

void Vi::Window::Draw(const sf::Drawable& drawable)
{
	m_pcWindow->draw(drawable);
}

