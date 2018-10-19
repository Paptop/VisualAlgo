#pragma once
#include <functional>
#include "Src/Vi/Sys/ReManager.h"
#include "Src/Vi/Sys/GoManager.h"
#include "Src/Vi/Go/GameObject.h"


namespace Vi
{

	class Dummy : public GameObject
	{
	public:

		virtual void Update(float fDeltaTime)
		{
		}

		virtual void Render(Window* pcWindow)
		{
			m_fProgress += 0.1;
			if (m_fProgress > 0.6)
			{
				if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
				{
					sf::Vector2i position = pcWindow->GetMousePos();
					sf::Vector2f bPosition = m_rect.getPosition();
					int maxY = bPosition.y + m_height;
					int maxX = bPosition.x + m_width;

					bool isY = position.y >= bPosition.y && position.y <= maxY;
					bool isX = position.x >= bPosition.x && position.x <= maxX;

					if (isX && isY)
					{
						std::cout << " X : " << pcWindow->GetMousePos().x << " Y : " << pcWindow->GetMousePos().y << std::endl;
						m_callback();
						m_fProgress = 0.0f;
					}
				}

				pcWindow->Draw(m_rect);
				pcWindow->Draw(m_text);
			}
		}

		sf::Vector2f GetPosition()
		{
			return m_rect.getPosition();
		}

		void SetPosition(Vector2 pos)
		{
			m_rect.setPosition(pos.m_x, pos.m_y);
			m_text.setPosition(pos.m_x, pos.m_y);
		}


		Dummy(std::function<void()> callback, std::string strName, int id)
		: m_callback(callback)
		{
			m_text.setFont(RE.GetFont());
			m_text.setFillColor(sf::Color::White);
			m_text.setCharacterSize(19);
			m_text.setOutlineColor(sf::Color::Black);
			m_text.setOutlineThickness(1);
			m_text.setStyle(sf::Text::Italic);
			m_text.setString(strName);

			m_rect.setSize(sf::Vector2f(100, 50));
			m_rect.setFillColor(sf::Color(255, id * 100, 00, 150));
			m_rect.setPosition(0.0f, id * 50 + 0.0f);
			m_text.setPosition(0.0f, id * 50 + 0.0f);

			m_width = 100;
			m_height = 50;
		}

	private:
		std::function< void()> m_callback;
		sf::RectangleShape m_rect;
		sf::Text m_text;
		int m_width;
		int m_height;
		float m_fProgress;
	};

};