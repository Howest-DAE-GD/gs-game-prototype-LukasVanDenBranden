#pragma once
class Player
{
public:
	Player();

	void DrawPlayer();
	void UpdatePlayer(float elapsedSec);

	void SetMovingUp(bool b);
	void SetMovingDown(bool b);
	void SetMovingLeft(bool b);
	void SetMovingRight(bool b);

	Point2f GetPosition();


private:
	//input
	bool m_MovingUp;
	bool m_MovingDown;
	bool m_MovingLeft;
	bool m_MovingRight;

	//player stats
	int m_Speed;


	//player
	Point2f m_Position;
	Point2f m_Velocity;
};

