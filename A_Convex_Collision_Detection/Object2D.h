#ifndef OBJECT2D_H
#define OBJECT2D_H

#include "Vector2D.h"

#include <vector>
#include <string>

class Object2D
{
public:
	Object2D() = default;
	Object2D(float x, float y) : m_coordinates({Vector2D(x, y)}) { }
	Object2D(const std::vector<Vector2D> &coordinates) : 
		m_coordinates(coordinates) { }
	virtual ~Object2D() = default;

	virtual void update() = 0;
	virtual void render() = 0;
	virtual std::string getType() const = 0;

	const std::vector<Vector2D> &getCoordinates() const
	{
		return m_coordinates;
	}

	std::vector<Vector2D>& getCoordinates()
	{
		return m_coordinates;
	}

	bool isPointed() const { return m_bIsPointed; }
	void isPointed(bool pointed) { m_bIsPointed = pointed; }
	bool isCollided() const { return m_bIsCollided; }
	void isCollided(bool collided) { m_bIsCollided = collided; }

protected:
	std::vector<Vector2D> m_coordinates;
	bool m_bIsPointed = false;
	bool m_bIsCollided = false;
};

#endif