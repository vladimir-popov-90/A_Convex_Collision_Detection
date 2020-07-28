#include "Mouse.h"
#include "Vector2D.h"
#include "Object2D.h"
#include "Application.h"

#include <GL/glut.h>
#include <iostream>
#include <vector>

void displayCallback()
{
	Application::getInstance().handleCollision();
	Application::getInstance().update();
	Application::getInstance().render();
}

void mouseCallback(int button, int state, int x, int y)
{
	Mouse::getInstance().isLeftClicked(button == GLUT_LEFT_BUTTON && 
		state == GLUT_DOWN);
	Mouse::getInstance().setX(x);
	Mouse::getInstance().setY(y);

	Application::getInstance().spotPointedObject();
}

void moveCallback(int x, int y)
{
	Mouse::getInstance().setMotionX(x);
	Mouse::getInstance().setMotionY(y);

	if (Mouse::getInstance().isLeftClicked())
	{
		glutPostRedisplay();
	}
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);

	Application::getInstance().setWindowWidth(1280);
	Application::getInstance().setWindowHeight(720);
	
	glutInitWindowSize(Application::getInstance().getWindowWidth(),
		Application::getInstance().getWindowHeight());
	glutInitWindowPosition(100, 100);
	glutCreateWindow("OpenGL Test");
	
	glutDisplayFunc(displayCallback);
	glutMouseFunc(mouseCallback);
	glutMotionFunc(moveCallback);
	
	gluOrtho2D(0.0, Application::getInstance().getWindowWidth() - 1, 
		Application::getInstance().getWindowHeight() - 1, 0.0);
	
	Application::getInstance().loadPolygons("polygons.txt");
	
	glutMainLoop();

	return 0;
}
