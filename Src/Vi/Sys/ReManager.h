#pragma once

#include "SFML/Graphics.hpp"
#include <iostream>
#include <assert.h>

namespace Vi
{

	class ReManager
	{
	public:
		static ReManager& GetInstance()
		{
			static ReManager manager;
			return manager;
		}

		inline const sf::Font& GetFont() { return m_font; }

	private:
		ReManager()
		{
			if (!m_font.loadFromFile("Assets/arial.ttf"))
			{
				std::cout << "Sys : Failed to load font" << std::endl;
			}
		}
	private:
		sf::Font m_font;

	};


	#define RE ReManager::GetInstance()
};