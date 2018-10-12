#ifndef TILE_H
#define TILE_H

#include "Src/Vi/Go/GameObject.h"
#include "Src/Vi/Global/Consts.h"
#include "Src/Vi/Sys/ReManager.h"

namespace Vi
{
	class Tile : public GameObject
	{
	public:
		virtual bool IsSolid() = 0;
		virtual int GetReward() = 0;
		virtual void IncrementDelay(float fDelta) {};

		inline int GetId()
		{
			return m_id;
		}

		sf::Vector2f GetSize()
		{ 
			sf::Vector2f res = m_rect.getSize();
			res.x += m_rect.getOutlineThickness();
			res.y += m_rect.getOutlineThickness();
			return res;
		}

		sf::Vector2f GetPosition()
		{
			return m_rect.getPosition();
		}

		sf::Vector2i GetIndex()
		{
			return m_pIndex;
		}

		void SetPosition(Vector2 pos)
		{
			m_rect.setPosition(pos.m_x, pos.m_y);
			m_text.setPosition(pos.m_x, pos.m_y);
		}

		void SetPosition(int row, int col)
		{
			float x = GetSize().x * col + kfOffset;
			float y = GetSize().y * row + kfOffset;
			SetPosition(Vector2(x, y));
		}

		void SetOffset(float x, float y)
		{
			m_rect.move(x, y);
			m_text.move(x, y);
		}

		void SetColIndex(int x)
		{
			m_pIndex.x = x;
		}

		void SetRowIndex(int y)
		{
			m_pIndex.y = y;
		}

		void SetIndex(int row, int col)
		{
			m_pIndex.x = col;
			m_pIndex.y = row;
		}

		void SetId(int id)
		{
			m_id = id;
			m_text.setString(std::to_string(m_id));
		}

		void SetColor(int r, int g, int b, int a)
		{
			m_rect.setFillColor(sf::Color(r, g, b, a));
		}

		void SetAlfa(float a)
		{
			float alfa = 0 + a * 255;
			sf::Color c = m_rect.getFillColor();
			c.a = alfa;
			m_rect.setFillColor(c);
		}

		void SetAlfa(int r, int g, int b, float a)
		{
			float alfa = 0 + a * 255;
			m_rect.setFillColor(sf::Color(r, g,b,alfa));
		}

		void SetLabelHidden(bool value)
		{
			m_isLabelHidden = value;
		}

		Tile() : m_isLabelHidden(true)
		{
			m_text.setFont(RE.GetFont());
			m_text.setFillColor(sf::Color::Green);
			m_text.setCharacterSize(20);
			m_text.setOutlineColor(sf::Color::Black);
			m_text.setOutlineThickness(1);
			m_text.setStyle(sf::Text::Bold);
		}
	protected:
		int m_id;
		sf::RectangleShape m_rect;
		sf::Text m_text;
		// TODO Change to Vector2i in VI
		sf::Vector2i m_pIndex;
		bool m_isLabelHidden;

	};


};


#endif // TILE_H
