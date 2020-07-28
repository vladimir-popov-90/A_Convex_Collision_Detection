#ifndef COLLISION_H
#define COLLISION_H

#include "Vector2D.h"
#include "Object2D.h"

#include <cstddef>

class Projection
{
public:
	Projection() = default;
	Projection(float min, float max) : m_min(min), m_max(max) { }

	void project(const Object2D &object, const Vector2D &axis)
	{
		m_min = axis.dotproduct(object.getCoordinates().at(0));
		m_max = m_min;

		for (std::size_t i = 1; i < object.getCoordinates().size(); ++i)
		{
			float temp = axis.dotproduct(object.getCoordinates().at(i));

			if (temp < m_min)
			{
				m_min = temp;
			}
			else if (temp > m_max)
			{
				m_max = temp;
			}
		}
	}

	float m_min = 0.0f;
	float m_max = 0.0f;
};

bool isOverlapping(const Projection &lhs, const Projection& rhs)
{
	return (rhs.m_min < lhs.m_max && rhs.m_min >= lhs.m_min) ||
		(lhs.m_min >= rhs.m_min && lhs.m_min < rhs.m_max);
}

std::vector<Vector2D> createAxes(const std::vector<Vector2D>& coordinates)
{
	std::vector<Vector2D> axes;

	for (std::size_t i = 0; i < coordinates.size(); ++i)
	{
		Vector2D edgeStartPoint = coordinates.at(i);
		Vector2D edgeEndPoint =
			coordinates.at((i + 1 == coordinates.size()) ? 0 : i + 1);
		Vector2D edge = edgeStartPoint - edgeEndPoint;
		Vector2D normal = edge.perproduct();
		axes.push_back(normal);
	}

	return axes;
}

bool checkCollision(const Object2D &lhs, const Object2D &rhs)
{
	std::vector<Vector2D> lhsAxes;
	if (lhs.getType() != "Point")
	{
		lhsAxes = createAxes(lhs.getCoordinates());
	}
	
	std::vector<Vector2D> rhsAxes;
	if (rhs.getType() != "Point")
	{
	rhsAxes = createAxes(rhs.getCoordinates());
	}

	for (const auto &axis : lhsAxes)
	{
		Projection lhsProjection;
		lhsProjection.project(lhs, axis);
		Projection rhsProjection;
		rhsProjection.project(rhs, axis);

		if (!isOverlapping(lhsProjection, rhsProjection))
		{
			return false;
		}
	}

	for (const auto &axis : rhsAxes)
	{
		Projection lhsProjection;
		lhsProjection.project(lhs, axis);
		Projection rhsProjection;
		rhsProjection.project(rhs, axis);

		if (!isOverlapping(lhsProjection, rhsProjection))
		{
			return false;
		}
	}

	return true;
}

#endif