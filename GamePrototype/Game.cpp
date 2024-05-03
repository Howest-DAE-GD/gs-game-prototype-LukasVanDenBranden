#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window },
	standingEnemiesAmount{},
	rotatingEnemiesAmount{},
	levelnr{},
	enterenceIsUp{},
	enterenceIsDown{},
	enterenceIsLeft{},
	enterenceIsRight{},
	enterenceDistance{},
	exitIsUp{},
	exitIsDown{},
	exitIsLeft{},
	exitIsRight{},
	exitDistance{},
	GameOver{},
	DoorIsClosed{},
	DoorIsClosing{},
	DoorClosingTimer{}
{
	srand(unsigned int(time(nullptr)));
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::UpdateRoom()
{
	//resetting all sides
	enterenceIsUp = exitIsDown;
	enterenceIsDown = exitIsUp;
	enterenceIsLeft = exitIsRight;
	enterenceIsRight = exitIsLeft;
	enterenceDistance = exitDistance;

	do
	{
		//get random side
		switch(rand() % 4)
		{
		case 0:
			exitIsUp = true;
			exitIsDown = false;
			exitIsLeft = false;
			exitIsRight = false;
			break;
		case 1:
			exitIsUp = false;
			exitIsDown = true;
			exitIsLeft = false;
			exitIsRight = false;
			break;
		case 2:
			exitIsUp = false;
			exitIsDown = false;
			exitIsLeft = true;
			exitIsRight = false;
			break;
		case 3:
			exitIsUp = false;
			exitIsDown = false;
			exitIsLeft = false;
			exitIsRight = true;
			break;
		}

	} while(enterenceIsUp && exitIsUp || enterenceIsDown && exitIsDown || enterenceIsLeft && exitIsLeft || enterenceIsRight && exitIsRight);

	if (exitIsUp || exitIsDown)
	{
		exitDistance = rand() % (1320) + 300.f;
	}
	else if (exitIsLeft || exitIsRight)
	{
		exitDistance = rand() % (480) + 300.f;
	}
	for (int i{}; i < standingEnemiesAmount; ++i)
	{
		standingEmenies[i] = StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition());
	}
	for (int i{}; i < rotatingEnemiesAmount; ++i)
	{
		rotatingEnemies[i] = RotatingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition());
	}

	AddNewEnemy();
	DoorIsClosed = false;
	DoorClosingTimer = 0.f;
}

void Game::AddNewEnemy()
{
	std::cout << levelnr << std::endl;
	if (levelnr < 5)
	{
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
	}
	else
	{
		rotatingEnemiesAmount++;
		rotatingEnemies.push_back(RotatingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		rotatingEnemiesAmount++;
		rotatingEnemies.push_back(RotatingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		rotatingEnemiesAmount++;
		rotatingEnemies.push_back(RotatingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
		standingEnemiesAmount++;
		standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width / screenScale, GetViewPort().height / screenScale), 75, myPlayer->GetPosition()));
	}
	levelnr++;
}

void Game::Initialize()
{
	screenScale = GetViewPort().width/1920.f;
	myPlayer = new Player{};

	UpdateRoom();
}

void Game::Cleanup( )
{
	delete myPlayer;
	myPlayer = nullptr;
}

void Game::Update( float elapsedSec )
{
	if (GameOver)
		elapsedSec /= 10;

	myPlayer->UpdatePlayer(elapsedSec);
	//player collision
	{
		//left
		if (myPlayer->GetPosition().x < 75 && myPlayer->GetVelocity().x < 0)
		{
			//if not in exit
			if (!(exitIsLeft && myPlayer->GetPosition().y > exitDistance - 150 && myPlayer->GetPosition().y < exitDistance + 150))
				myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
		}
		//right
		if (myPlayer->GetPosition().x > 1845 && myPlayer->GetVelocity().x > 0)
		{
			//if not in exit
			if (!(exitIsRight && myPlayer->GetPosition().y > exitDistance - 150 && myPlayer->GetPosition().y < exitDistance + 150))
				myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
		}
		//down
		if (myPlayer->GetPosition().y < 75 && myPlayer->GetVelocity().y < 0)
		{
			//if not in exit
			if (!(exitIsDown && myPlayer->GetPosition().x > exitDistance - 150 && myPlayer->GetPosition().x < exitDistance + 150))
				myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
		}
		//up
		if (myPlayer->GetPosition().y > 1005 && myPlayer->GetVelocity().y > 0)
		{
			//if not in exit
			if (!(exitIsUp && myPlayer->GetPosition().x > exitDistance - 150 && myPlayer->GetPosition().x < exitDistance + 150))
				myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
		}

		//checking walls of doors
		if (!DoorIsClosed)
		{
			//left or right
			if ((myPlayer->GetPosition().x < 75 && enterenceIsLeft) || (myPlayer->GetPosition().x > 1845 && enterenceIsRight))
			{
				if (myPlayer->GetVelocity().y > 0 && myPlayer->GetPosition().y > enterenceDistance + 125)
					myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
				if (myPlayer->GetVelocity().y < 0 && myPlayer->GetPosition().y < enterenceDistance - 125)
					myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
			}
			//up or down
			if ((myPlayer->GetPosition().y < 75 && enterenceIsDown) || (myPlayer->GetPosition().y > 1005 && enterenceIsUp))
			{
				if (myPlayer->GetVelocity().x > 0 && myPlayer->GetPosition().x > enterenceDistance + 125)
					myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
				if (myPlayer->GetVelocity().x < 0 && myPlayer->GetPosition().x < enterenceDistance - 125)
					myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
			}
		}

		//left or right
		if ((myPlayer->GetPosition().x < 75 && exitIsLeft) || (myPlayer->GetPosition().x > 1845 && exitIsRight))
		{
			if (myPlayer->GetVelocity().y > 0 && myPlayer->GetPosition().y > exitDistance + 125 && myPlayer->GetPosition().y < exitDistance + 130)
				myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
			if (myPlayer->GetVelocity().y < 0 && myPlayer->GetPosition().y < exitDistance - 125 && myPlayer->GetPosition().y > exitDistance - 130)
				myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x, -myPlayer->GetVelocity().y * 0.95f));
		}
		//up or down
		if ((myPlayer->GetPosition().y < 75 && exitIsDown) || (myPlayer->GetPosition().y > 1005 && exitIsUp))
		{
			if (myPlayer->GetVelocity().x > 0 && myPlayer->GetPosition().x > exitDistance + 125 && myPlayer->GetPosition().x < exitDistance + 130)
				myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
			if (myPlayer->GetVelocity().x < 0 && myPlayer->GetPosition().x < exitDistance - 125 && myPlayer->GetPosition().x > exitDistance - 130)
				myPlayer->SetVelocity(Point2f(-myPlayer->GetVelocity().x * 0.95f, myPlayer->GetVelocity().y));
		}


		//check for going out of screen
		if (myPlayer->GetPosition().x < 0)
		{
			myPlayer->SetPosition(Point2f(1920, myPlayer->GetPosition().y));
			myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x * 0.5f, myPlayer->GetVelocity().y * 0.5f));
			UpdateRoom();
		}
		if (myPlayer->GetPosition().x > 1920)
		{
			myPlayer->SetPosition(Point2f(0, myPlayer->GetPosition().y));
			myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x * 0.5f, myPlayer->GetVelocity().y * 0.5f));
			UpdateRoom();
		}
		if (myPlayer->GetPosition().y < 0)
		{
			myPlayer->SetPosition(Point2f(myPlayer->GetPosition().x, 1080));
			myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x * 0.5f, myPlayer->GetVelocity().y * 0.5f));
			UpdateRoom();
		}
		if (myPlayer->GetPosition().y > 1080)
		{
			myPlayer->SetPosition(Point2f(myPlayer->GetPosition().x, 0));
			myPlayer->SetVelocity(Point2f(myPlayer->GetVelocity().x * 0.5f, myPlayer->GetVelocity().y * 0.5f));
			UpdateRoom();
		}
	}

	for (int i{}; i < rotatingEnemiesAmount; ++i)
	{
		rotatingEnemies[i].Update(elapsedSec);
	}

	//check death
	for (int i{}; i < standingEnemiesAmount; ++i)
	{
		if (utils::IsOverlapping(Circlef(standingEmenies[i].m_Position, standingEmenies[i].m_Size), Circlef(myPlayer->GetPosition(), 25)))
		{
			GameOver = true;
		}
	}
	for (int i{}; i < rotatingEnemiesAmount; ++i)
	{
		if (utils::IsOverlapping(Circlef(rotatingEnemies[i].m_Position, rotatingEnemies[i].m_Size), Circlef(myPlayer->GetPosition(), 25)))
		{
			GameOver = true;
		}
	}

	//closing doors
	if (DoorIsClosing)
	{
		if (DoorClosingTimer * 100 > 150)
		{
			DoorClosingTimer = 0.f;
			DoorIsClosing = false;
			DoorIsClosed = true;
		}
		else
			DoorClosingTimer += elapsedSec*6;
	}
	else
	{
		if (myPlayer->GetPosition().x > 50 && myPlayer->GetPosition().x < 1870 && myPlayer->GetPosition().y > 50 && myPlayer->GetPosition().y < 1030 && !DoorIsClosed)
		{
			DoorIsClosing = true;
		}
	}

}

void Game::Draw( ) const
{
	glPushMatrix();
	glScalef(screenScale, screenScale, 0.f);
	ClearBackground();

	utils::SetColor(Color4f(1, 1, 1, 1));
	utils::FillRect(0, 1030, 1920, 50);
	utils::FillRect(0, 0, 1920, 50);
	utils::FillRect(1870, 0, 50, 1080);
	utils::FillRect(0, 0, 50, 1080);

	utils::SetColor(Color4f(0, 0, 0, 1));
	//draw enterence
	if (enterenceIsUp)
	{
		if (!DoorIsClosed)
			utils::FillRect(enterenceDistance - 150 + DoorClosingTimer * 100, 1029, 300 - DoorClosingTimer * 200, 56);
	}
	if (enterenceIsDown)
	{
		if (!DoorIsClosed)
			utils::FillRect(enterenceDistance - 150 + DoorClosingTimer * 100, -5, 300 - DoorClosingTimer * 200, 56);
	}
	if (enterenceIsLeft)
	{
		if (!DoorIsClosed)
			utils::FillRect(-5, enterenceDistance - 150 + DoorClosingTimer * 100, 56, 300 - DoorClosingTimer * 200);
	}
	if (enterenceIsRight)
	{
		if (!DoorIsClosed)
			utils::FillRect(1869, enterenceDistance - 150 + DoorClosingTimer * 100, 56, 300 - DoorClosingTimer * 200);
	}
	//drawing exit
	if (exitIsUp)
	{
		utils::FillRect(exitDistance - 150, 1029, 300, 56);
	}
	if (exitIsDown)
	{
		utils::FillRect(exitDistance - 150, -5, 300, 56);
	}
	if (exitIsLeft)
	{
		utils::FillRect(-5, exitDistance - 150, 56, 300);
	}
	if (exitIsRight)
	{
		utils::FillRect(1869, exitDistance - 150, 56, 300);
	}

	//draw player
	myPlayer->DrawPlayer();

	//draw enemies
	for (int i{}; i < standingEnemiesAmount; ++i)
	{
		standingEmenies[i].Draw();
	}
	for (int i{}; i < rotatingEnemiesAmount; ++i)
	{
		rotatingEnemies[i].Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
{

	if (!GameOver)
	{
		switch (e.keysym.sym)
		{
		case SDLK_w:
			myPlayer->SetMovingUp(true);
			break;
		case SDLK_a:
			myPlayer->SetMovingLeft(true);
			break;
		case SDLK_s:
			myPlayer->SetMovingDown(true);
			break;
		case SDLK_d:
			myPlayer->SetMovingRight(true);
			break;
		}
	}
}

void Game::ProcessKeyUpEvent( const SDL_KeyboardEvent& e )
{
	switch (e.keysym.sym)
	{
	case SDLK_w:
		myPlayer->SetMovingUp(false);
		break;
	case SDLK_a:
		myPlayer->SetMovingLeft(false);
		break;
	case SDLK_s:
		myPlayer->SetMovingDown(false);
		break;
	case SDLK_d:
		myPlayer->SetMovingRight(false);
		break;
	case SDLK_n:
		UpdateRoom();
		break;
	}
}

void Game::ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e )
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent( const SDL_MouseButtonEvent& e )
{
	
}

void Game::ProcessMouseUpEvent( const SDL_MouseButtonEvent& e )
{

}

void Game::ClearBackground( ) const
{
	if (GameOver)
		glClearColor(0.2f, 0.0f, 0.0f, 1.0f);
	else
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}
