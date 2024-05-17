#include "pch.h"
#include "StandingEnemy.h"


StandingEnemy::StandingEnemy()
	: m_Position{},
	m_Size{20}
{
}

StandingEnemy::StandingEnemy(Point2f screenSize, float border, Point2f playerPos)
	: m_Position{},
	m_Size{ 20 }
{
	do
	{
		m_Position = Point2f(rand() % int(screenSize.x - 2 * border) + border, rand() % int(screenSize.y - 2 * border) + border);
	} while (utils::GetDistance(playerPos, m_Position) < 200);
}

void StandingEnemy::Draw()const
{
	utils::SetColor(Color4f(0.859f, 0.302f, 0.145f, 1));
	utils::FillEllipse(m_Position, m_Size, m_Size);
}
