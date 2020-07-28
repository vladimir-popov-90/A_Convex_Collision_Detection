#include "Application.h"
#include "Collision.h"
#include "Polygon.h"
#include "Mouse.h"

#include <GL/glut.h>
#include <cstddef>
#include <fstream>
#include <iterator>
#include <iostream>

Application* Application::s_pInstance = nullptr;

Application& Application::getInstance()
{
	if (s_pInstance == nullptr)
	{
		s_pInstance = new Application();
	}

	return *s_pInstance;
}

void Application::handleCollision()
{
	for (auto &object : m_objects)
	{
		if (object->isCollided())
		{
			object->isCollided(false);
		}
	}

	for (std::size_t i = 0; i < m_objects.size() - 1; ++i)
	{
		for (std::size_t j = i + 1; j < m_objects.size(); ++j)
		{
			if (checkCollision(*m_objects.at(i), *m_objects.at(j)))
			{
				m_objects.at(i)->isCollided(true);
				m_objects.at(j)->isCollided(true);
			}
		}
	}
}

void Application::update()
{
	for (auto &object : m_objects)
	{
		object->update();
	}
}

void Application::render()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	for (auto &object : m_objects)
	{
		object->render();
	}

	glFlush();
	glutSwapBuffers();
}

void Application::loadPolygons(const std::string& fileName)
{
	std::ifstream ifile(fileName, std::ifstream::in);

	if (ifile.is_open())
	{
		std::istream_iterator<std::string> begin(ifile), eof;
		std::vector<std::string> file(begin, eof);
		std::vector<Vector2D> coordinates;

		bool load = false;
		bool stop = false;

		for (std::size_t i = 0; i < file.size(); ++i)
		{
			if (file.at(i) == "begin") { load = true; ++i; }
			if (file.at(i) == "end") { stop = true; load = false; }

			if (load)
			{
				coordinates.emplace_back(std::stof(file.at(i)), 
					std::stof(file.at(i+1)));
				++i;
			}
			
			if (stop)
			{
				m_objects.push_back(std::make_shared<Polygon>(coordinates));
				coordinates.clear();
				stop = false;
			}
		}

		ifile.close();
	}
}

void Application::spotPointedObject()
{
	for (auto &object : m_objects)
	{
		if (object->isPointed())
		{
			object->isPointed(false);
		}
	}

	// the last object in the queue on the render
	// is the top one that will be appeared on the scene

	for (auto beg = m_objects.rbegin();
		beg != m_objects.rend(); ++beg)
	{
		if (checkCollision(**beg, Mouse::getInstance().getPoint()))
		{
			(**beg).isPointed(true);
			break;
		}
	}
}