#ifndef WINDOW_H
#define WINDOW_H

#include "SFML/Graphics.hpp"

namespace Vi
{
	class Window
	{
	public:
		bool IsOpen() const;
		void Close();
		void Clear();
		bool PollEvent(sf::Event& event);
		void Diplay();
		void Draw(const sf::Drawable& drawable);

		Window();
		~Window();
	private:
		sf::RenderWindow* m_pcWindow;
	};
}

#endif // Window