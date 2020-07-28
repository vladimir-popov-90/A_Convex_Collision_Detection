#ifndef APPLICATION_H
#define APPLICATION_H

#include "Object2D.h"

#include <vector>
#include <string>
#include <memory>

class Application
{
public:
	Application() = default;
	Application(const Application&) = delete;
	Application& operator=(const Application&) = delete;

	static Application& getInstance();

	void handleCollision();
	void update();
	void render();

	void loadPolygons(const std::string &);
	void spotPointedObject();

	int getWindowWidth() const { return m_windowWidth; }
	int getWindowHeight() const { return m_windowHeight; }

	void setWindowWidth(int width) { m_windowWidth = width; }
	void setWindowHeight(int height) { m_windowHeight = height; }

	std::vector<std::shared_ptr<Object2D>> m_objects;

private:
	static Application* s_pInstance;
	
	int m_windowWidth = 400;
	int m_windowHeight = 400;
};

#endif