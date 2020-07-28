#ifndef POLYGON_H
#define POLYGON_H

#include "Object2D.h"
#include "Vector2D.h"

#include <vector>

class Polygon : public Object2D
{
public:
	Polygon() = default;
	Polygon(const std::vector<Vector2D> &coordinates) :
		Object2D(coordinates)
	{
		randomizeColor();
	}

	void update() override;
	void render() override;
	std::string getType() const override { return "Polygon"; }

	void randomizeColor();

private:
	float m_color_r = 0;
	float m_color_g = 0;
	float m_color_b = 0;

	static int m_randomShift;
};

#endif