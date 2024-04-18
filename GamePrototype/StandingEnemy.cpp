#include "pch.h"
#include "StandingEnemy.h"


StandingEnemy::StandingEnemy()
	: m_Position{},
	m_Size{10}
{
}

StandingEnemy::StandingEnemy(Point2f screenSize, float border, Point2f playerPos)
	: m_Position{rand()%int(screenSize.x-2*int(border))-border, rand()%int(screenSize.x - 2 * int(border))-border },
	m_Size{ 10 }
{
	while (utils::GetDistance(playerPos, m_Position) < 100)
	{
		m_Position = Point2f(rand() % int(screenSize.x - 2 * int(border)) - border, rand() % int(screenSize.x - 2 * int(border)) - border);
	}
}

void StandingEnemy::Draw()const
{
	utils::SetColor(Color4f(1, 0, 0, 1));
	utils::FillEllipse(m_Position, m_Size, m_Size);
}

void StandingEnemy::Update(float elapsedSec)
{
}
