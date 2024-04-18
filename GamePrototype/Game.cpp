#include "pch.h"
#include "Game.h"

Game::Game( const Window& window ) 
	:BaseGame{ window },
	standingEnemiesAmount{}
{
	srand(unsigned int(time(nullptr)));
	Initialize();
}

Game::~Game( )
{
	Cleanup( );
}

void Game::Initialize()
{

	screenScale = GetViewPort().width/1366.f;
	myPlayer = new Player{};
}

void Game::Cleanup( )
{
	delete myPlayer;
	myPlayer = nullptr;
}

void Game::Update( float elapsedSec )
{
	myPlayer->UpdatePlayer(elapsedSec);
}

void Game::Draw( ) const
{
	glPushMatrix();
	glScalef(screenScale, screenScale, 0.f);
	ClearBackground();
	myPlayer->DrawPlayer();
	for (int i{}; i < standingEnemiesAmount; ++i)
	{
		standingEmenies[i].Draw();
	}
	glPopMatrix();
}

void Game::ProcessKeyDownEvent( const SDL_KeyboardEvent & e )
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
	standingEnemiesAmount++;
	standingEmenies.push_back(StandingEnemy(Point2f(GetViewPort().width/ screenScale, GetViewPort().height/ screenScale), 10, myPlayer->GetPosition()));
	
}

void Game::ClearBackground( ) const
{
	glClearColor( 0.0f, 0.0f, 0.3f, 1.0f );
	glClear( GL_COLOR_BUFFER_BIT );
}
