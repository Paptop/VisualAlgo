#include "Src/Vi/Math/Vector2.h"


Vi::Vector2::Vector2()
: m_x(0)
, m_y(0)
{
}

Vi::Vector2::Vector2(float x, float y)
: m_x(x)
, m_y(y)
{
}

Vi::Vector2::Vector2(const Vector2& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
}

Vi::Vector2 Vi::Vector2::operator+(const Vector2& vec)
{
	Vector2 res;
	res.m_x = m_x + vec.m_x;
	res.m_y = m_y + vec.m_y;
	return res;
}

Vi::Vector2 Vi::Vector2::operator-(const Vector2& vec)
{
	Vector2 res;
	res.m_x = m_x - vec.m_x;
	res.m_y = m_y - vec.m_y;
	return res;
}

Vi::Vector2 Vi::Vector2::operator*(const Vector2& vec)
{
	Vector2 res;
	res.m_x = m_x * vec.m_x;
	res.m_y = m_y * vec.m_y;
	return res;
}

Vi::Vector2 Vi::Vector2::operator/(const Vector2& vec)
{
	Vector2 res;
	res.m_x = m_x / vec.m_x;
	res.m_y = m_y / vec.m_y;
	return res;
}

Vi::Vector2& Vi::Vector2::operator=(const Vector2& vec)
{
	m_x = vec.m_x;
	m_y = vec.m_y;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator*=(const Vector2& vec)
{
	m_x *= vec.m_x;
	m_y *= vec.m_y;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator*=(float value)
{
	m_x *= value;
	m_y *= value;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator+=(const Vector2& vec)
{
	m_x += vec.m_x;
	m_y += vec.m_y;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator+=(float value)
{
	m_x += value;
	m_y += value;
	return *this;
}


Vi::Vector2& Vi::Vector2::operator-=(const Vector2& vec)
{
	m_x -= vec.m_x;
	m_y -= vec.m_y;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator-=(float value)
{
	m_x -= value;
	m_y -= value;
	return *this;
}

Vi::Vector2& Vi::Vector2::operator/=(const Vector2& vec)
{
	m_x /= vec.m_x;
	m_y /= vec.m_y;
	return *this;
}


Vi::Vector2& Vi::Vector2::operator/=(float value)
{
	m_x /= value;
	m_y /= value;
	return *this;
}


// SFML VECTOR

Vi::Vector2& Vi::Vector2::operator=(const sf::Vector2f& vec)
{
	m_x = vec.x;
	m_y = vec.y;
	return *this;
}
