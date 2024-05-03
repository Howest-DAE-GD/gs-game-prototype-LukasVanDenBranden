#pragma once
#include "utils.h"
#include <iostream>

class StandingEnemy
{
public:
	StandingEnemy();
	StandingEnemy(Point2f screenSize, float border, Point2f playerPos);

	void Draw()const;
	Point2f m_Position;
	float m_Size;

private:
};

