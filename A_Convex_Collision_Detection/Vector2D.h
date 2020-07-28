#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
	friend Vector2D operator-(const Vector2D &, const Vector2D &);
public:

	Vector2D() = default;
	Vector2D(float x, float y) : m_x(x), m_y(y) { }

	float getX() const { return m_x; }
	float getY() const { return m_y; }

	void setX(const float x) { m_x = x; }
	void setY(const float y) { m_y = y; }

	Vector2D perproduct() const;
	float dotproduct(const Vector2D &) const;
	float length() const;
	Vector2D getNormalized() const;

private:
	float m_x = 0.0f;
	float m_y = 0.0f;
};

Vector2D operator-(const Vector2D &, const Vector2D &);

#endif