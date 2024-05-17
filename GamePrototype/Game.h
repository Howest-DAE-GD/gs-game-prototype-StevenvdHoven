#pragma once
#include "BaseGame.h"
#include "utils.h"
#include <vector>
#include <Texture.h>
#include "AttackManager.h"

#define player1Color Color4f{0.f,1.f,0.f,1.f}
#define player2Color Color4f{0.f,0.f,0.75f,1.f}
#define playerRadius 50




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

	// FUNCTIONS
	void Initialize();
	void Cleanup( );
	void ClearBackground( ) const;

	void SimulatePlayerMovement(float elapsedSec);
	void CheckMaxDistance();
	void HitRope();
	void CheckInput();

	void RestartGame();
	void UpdateText();

	void DrawPlayers() const;


	// VARIABLES
	float m_MaxPlayerDistance;
	float m_PlayerSpeed;

	Point2f m_Player1Position;
	Point2f m_Player2Position;

	Vector2f m_Player1Direction;
	Vector2f m_Player2Direction;

	std::vector<int> m_CurrentInput;

	int m_CurrentBulletSpawn;

	float m_Timer;
	int m_Time;

	Texture* m_TimerText;
	TTF_Font* m_Font;

	AttackManager* m_AttackManager;
};