#include "pch.h"
#include "RotatingEnemy.h"
#include "utils.h"

RotatingEnemy::RotatingEnemy()
	: m_Position{},
	m_Size{ 20 },
	m_Center{},
	m_Direction{},
	m_Timer{}
{
	m_Timer = float(rand() % 100)/10;
}

RotatingEnemy::RotatingEnemy(Point2f screenSize, float border, Point2f playerPos)
	: m_Position{},
		m_Size{ 20 },
	m_Center{},
	m_Direction{},
	m_Timer{}
{
	m_Direction = bool(rand() % 2);
	m_Timer = float(rand() % 6282) / 1000;
	border += 100;
	do
	{
		m_Center = Point2f(rand() % int(screenSize.x - 2 * border) + border, rand() % int(screenSize.y - 2 * border) + border);
	} while (utils::GetDistance(playerPos, m_Center) < 300);
}

void RotatingEnemy::Draw() const
{
	utils::SetColor(Color4f(1, 0, 0.7f, 1));
	utils::FillEllipse(m_Position, m_Size, m_Size);
	//animation
	if (m_Direction)
	{
		utils::SetColor(Color4f(1, 0, 0.7f, 0.3f));
		utils::FillEllipse(Point2f(m_Center.x + 100 * sin(m_Timer - 0.4f), m_Center.y + 100 * cos(m_Timer - 0.4f)), m_Size / 1.5f, m_Size / 1.5f);
		utils::SetColor(Color4f(1, 0, 0.7f, 0.2f));
		utils::FillEllipse(Point2f(m_Center.x + 100 * sin(m_Timer - 0.7f), m_Center.y + 100 * cos(m_Timer - 0.7f)), m_Size / 2, m_Size / 2);
	}
	else
	{
		utils::SetColor(Color4f(1, 0, 0.7f, 0.3f));
		utils::FillEllipse(Point2f(m_Center.x + 100 * sin(-m_Timer + 0.4f), m_Center.y + 100 * cos(-m_Timer + 0.4f)), m_Size / 1.5f, m_Size / 1.5f);
		utils::SetColor(Color4f(1, 0, 0.7f, 0.2f));
		utils::FillEllipse(Point2f(m_Center.x + 100 * sin(-m_Timer + 0.7f), m_Center.y + 100 * cos(-m_Timer + 0.7f)), m_Size / 2, m_Size / 2);
	}
}

void RotatingEnemy::Update(float elapsedSec)
{
	m_Timer += elapsedSec;


	if (m_Timer >= 6.282f)
		m_Timer -= 6.282f;

	if(m_Direction)
		m_Position = Point2f(m_Center.x + 100 * sin(m_Timer), m_Center.y + 100 * cos(m_Timer));
	else
		m_Position = Point2f(m_Center.x + 100 * sin(-m_Timer), m_Center.y + 100 * cos(-m_Timer));
}

