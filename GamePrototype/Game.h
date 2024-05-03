#pragma once
#include "BaseGame.h"
#include "Player.h"
#include "StandingEnemy.h"
#include "RotatingEnemy.h"
#include <vector>
#include <iostream>

class Game : public BaseGame
{
public:
	explicit Game( const Window& window );
	Game(const Game& other) = delete;
	Game& operator=(const Game& other) = delete;
	Game( Game&& other) = delete;
	Game& operator=(Game&& other) = delete;
	// http://isocpp.github.io/CppCoreGuidelines/CppCoreGuidelines#Rh-override
	~Game();

	void Update( float elapsedSec ) override;
	void Draw( ) const override;

	// Event handling
	void ProcessKeyDownEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessKeyUpEvent( const SDL_KeyboardEvent& e ) override;
	void ProcessMouseMotionEvent( const SDL_MouseMotionEvent& e ) override;
	void ProcessMouseDownEvent( const SDL_MouseButtonEvent& e ) override;
	void ProcessMouseUpEvent( const SDL_MouseButtonEvent& e ) override;

private:
	float screenScale;
	int levelnr;

	bool GameOver;
	bool DoorIsClosed;
	bool DoorIsClosing;
	float DoorClosingTimer;

	Player* myPlayer;

	int standingEnemiesAmount;
	std::vector<StandingEnemy> standingEmenies;
	int rotatingEnemiesAmount;
	std::vector<RotatingEnemy> rotatingEnemies;


	bool enterenceIsUp;
	bool enterenceIsDown;
	bool enterenceIsLeft;
	bool enterenceIsRight;
	float enterenceDistance;

	bool exitIsUp;
	bool exitIsDown;
	bool exitIsLeft;
	bool exitIsRight;
	float exitDistance;
	
	void UpdateRoom();
	void AddNewEnemy();

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;
};