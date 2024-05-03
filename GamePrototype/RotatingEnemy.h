#pragma once
class RotatingEnemy
{
public:
	RotatingEnemy();
	RotatingEnemy(Point2f screenSize, float border, Point2f playerPos);

	void Draw()const;
	void Update(float elapsedSec);
	Point2f m_Position;
	float m_Size;
private:
	Point2f m_Center;
	bool m_Direction;
	float m_Timer;
};

