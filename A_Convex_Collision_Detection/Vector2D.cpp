#include "Vector2D.h"

#include <cmath>

Vector2D Vector2D::perproduct() const
{
	return Vector2D(-m_y, m_x);
}

float Vector2D::dotproduct(const Vector2D& rhs) const
{
	return m_x * rhs.getX() + m_y * rhs.getY();
}

float Vector2D::length() const
{
	return sqrt(m_x * m_x + m_y * m_y);
}

Vector2D Vector2D::getNormalized() const
{
	return Vector2D(m_x / length(), m_y / length());
}

Vector2D operator-(const Vector2D& lhs, const Vector2D& rhs)
{
	return Vector2D(lhs.m_x - rhs.m_x, lhs.m_y - rhs.m_y);
}