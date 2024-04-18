#include "pch.h"
#include "Player.h"
#include "utils.h"
#include <iostream>

Player::Player()
	: m_MovingUp{},
	m_MovingDown{},
	m_MovingLeft{},
	m_MovingRight{},
	m_Speed{ 500 }
{
}

void Player::DrawPlayer()
{
	utils::SetColor(Color4f(0, 1, 0, 1));
	utils::FillEllipse(m_Position, 10, 10);
}

void Player::UpdatePlayer(float elapsedSec)
{
	if (m_MovingUp)
	{
		if(m_Velocity.y < 0)
			m_Velocity.y *= 0.97f;
		m_Velocity.y += m_Speed * elapsedSec;
	}
	if (m_MovingDown)
	{
		if (m_Velocity.y > 0)
			m_Velocity.y *= 0.97f;
		m_Velocity.y -= m_Speed * elapsedSec;
	}
	if (m_MovingLeft)
	{
		if (m_Velocity.x > 0)
			m_Velocity.x *= 0.97f;
		m_Velocity.x -= m_Speed * elapsedSec;
	}
	if (m_MovingRight)
	{
		if (m_Velocity.x < 0)
			m_Velocity.x *= 0.97f;
		m_Velocity.x += m_Speed * elapsedSec;
	}

	//adding drag
	if (!m_MovingLeft && !m_MovingRight)
		m_Velocity.x *= 0.97f;
	if (!m_MovingUp && !m_MovingDown)
		m_Velocity.y *= 0.97f;

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;
}

void Player::SetMovingUp(bool b)
{
	m_MovingUp = b;
}

void Player::SetMovingDown(bool b)
{
	m_MovingDown = b;
}

void Player::SetMovingLeft(bool b)
{
	m_MovingLeft = b;
}

void Player::SetMovingRight(bool b)
{
	m_MovingRight = b;
}

Point2f Player::GetPosition()
{
	return m_Position;
}