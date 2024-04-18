#pragma once
#include "utils.h"

class StandingEnemy
{
public:
	StandingEnemy();
	StandingEnemy(Point2f screenSize, float border, Point2f playerPos);

	void Draw()const;
	void Update(float elapsedSec);

private:
	Point2f m_Position;
	float m_Size;
};

