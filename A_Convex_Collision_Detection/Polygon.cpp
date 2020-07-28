#include "Polygon.h"
#include "Mouse.h"
#include "Application.h"

#include <GL/glut.h>
#include <iostream>
#include <ctime>

int Polygon::m_randomShift = 1;

void Polygon::update()
{
	if (Mouse::getInstance().isLeftClicked() && isPointed())
	{
		float deltaX = 
			Mouse::getInstance().getMotionX() - Mouse::getInstance().getX();
		float deltaY = 
			Mouse::getInstance().getMotionY() - Mouse::getInstance().getY();

		Mouse::getInstance().setX(Mouse::getInstance().getMotionX());
		Mouse::getInstance().setY(Mouse::getInstance().getMotionY());

		for (auto &coordinate : m_coordinates)
		{
			coordinate.setX(coordinate.getX() + deltaX);
			coordinate.setY(coordinate.getY() + deltaY);
		}
	}
}

void Polygon::render()
{
	glBegin(GL_POLYGON);

	if (isCollided())
	{
		glColor3f(1.0f - m_color_r, 1.0f - m_color_g, 1.0f - m_color_b);
	}
	else
	{
		glColor3f(m_color_r, m_color_g, m_color_b);
	}

	for (auto &coord : m_coordinates)
	{
		glVertex2f(coord.getX(), coord.getY());
	}

	glEnd();
}

void Polygon::randomizeColor()
{
	std::srand(std::time(0) + m_randomShift);
	++m_randomShift;
	m_color_r = static_cast<float>((std::rand() % 10) + 1) / 10;
	m_color_g = static_cast<float>((std::rand() % 10) + 1) / 10;
	m_color_b = static_cast<float>((std::rand() % 10) + 1) / 10;
}
