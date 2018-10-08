#ifndef VECTOR2_H
#define VECTOR2_H
#include "SFML/System/Vector2.hpp "

namespace Vi
{
	struct Vector2
	{
		float m_x, m_y;

		Vector2(float x, float y);
		Vector2();
		Vector2(const Vector2& vec);

		// Vector op Vector
		Vector2 operator+(const Vector2& vec);
		Vector2 operator-(const Vector2& vec);
		Vector2 operator*(const Vector2& vec);
		Vector2 operator/(const Vector2& vec);
		Vector2& operator*=(const Vector2& vec);
		Vector2& operator+=(const Vector2& vec);
		Vector2& operator-=(const Vector2& vec);
		Vector2& operator/=(const Vector2& vec);

		Vector2& operator=(const Vector2& vec);

		// Vector op Constant
		Vector2& operator-=(float value);
		Vector2& operator+=(float value);
		Vector2& operator*=(float value);
		Vector2& operator/=(float value);

		// SFML conversion
		Vector2& operator=(const sf::Vector2f& vec);
	};

}

#endif
