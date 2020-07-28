#ifndef MOUSE_H
#define MOUSE_H

#include "Object2D.h"
#include "Vector2D.h"

class Mouse
{
public:
	class Point : public Object2D
	{
	public:
		Point() : Object2D(Mouse::getInstance().getX(), 
			Mouse::getInstance().getY()) { }

		void update() override { }
		void render() override { }
		std::string getType() const { return "Point"; }
	};

	Mouse() = default;
	Mouse(const Mouse&) = delete;
	Mouse& operator=(const Mouse&) = delete;

	static Mouse& getInstance();

	float getX() const { return m_x; }
	float getY() const { return m_y; }
	float getMotionX() const { return m_motionX; }
	float getMotionY() const { return m_motionY; }

	void setX(float x) { m_x = x; }
	void setY(float y) { m_y = y; }
	void setMotionX(float x) { m_motionX = x; }
	void setMotionY(float y) { m_motionY = y; }

	Point getPoint() { return Point(); }

	bool isLeftClicked() const { return m_bLeftClicked; }
	void isLeftClicked(bool leftClicked) { m_bLeftClicked = leftClicked; }

private:
	static Mouse *s_pInstance;

	float m_x = 0.0f;
	float m_y = 0.0f;
	float m_motionX = 0.0f;
	float m_motionY = 0.0f;

	bool m_bLeftClicked = false;
};

#endif