#include "pch.h"
#include "Game.h"
#include "Attack.h"

Game::Game(const Window& window)
	:BaseGame{ window },

	m_MaxPlayerDistance{ 800 },
	m_PlayerSpeed{ 200 },
	m_Player1Position{ Point2f(window.width * 0.5f,window.height * 0.5f) - Vector2f(100,0) },
	m_Player2Position{ Point2f(window.width * 0.5f,window.height * 0.5f) + Vector2f(100,0) },
	m_Player1Direction{},
	m_Player2Direction{},
	m_CurrentBulletSpawn{ 20 },
	m_Time{ 0 },
	m_Timer{0},
	m_HitCooldown{-1},
	m_PlayersHit{false},
	m_TimerText{nullptr},
	m_Font{nullptr},
	m_AttackManager{new AttackManager()},
	m_WaveManager{new WaveManager(m_AttackManager)},
	m_RecoverSpawner{new RecoverSpawner()}
{
	Initialize();
}

Game::~Game()
{
	Cleanup();
}

void Game::Initialize()
{
	m_Font = TTF_OpenFont("arial.ttf", 20);
	UpdateText();
	m_HitSound = new SoundEffect{ "Audio/hitHurt.wav" };
	m_CollectSound = new SoundEffect{ "Audio/pickupCoin.wav" };
}

void Game::Cleanup()
{
	TTF_CloseFont(m_Font);
	m_Font = nullptr;

	delete m_TimerText;
	delete m_AttackManager;
	delete m_WaveManager;
	delete m_RecoverSpawner;
	delete m_HitSound;
	delete m_CollectSound;
}

void Game::Update(float elapsedSec)
{
	m_Timer -= elapsedSec;
	if (m_Timer <= 0) {
		m_Time++;
		m_Timer = 1.f;
		UpdateText();

	}

	if (m_PlayersHit)
	{
		if (m_HitCooldown > 0)
		{
			m_HitCooldown -= elapsedSec;
			if (m_HitCooldown <= 0)
			{
				m_PlayersHit = false;
			}
		}
	}

	CheckInput();

	SimulatePlayerMovement(elapsedSec);
	CheckMaxDistance();

	m_AttackManager->Update(elapsedSec);
	m_WaveManager->Update(elapsedSec);
	m_RecoverSpawner->Update(elapsedSec, m_MaxPlayerDistance);

	const std::vector<Circlef> players
	{
		Circlef{m_Player1Position,playerRadius},
		Circlef{m_Player2Position,playerRadius}
	};

	Attack* hitAttack{ m_AttackManager->CheckCollisionAttacks(players) };
	if (hitAttack != nullptr && !m_PlayersHit) 
	{
		hitAttack->SetActive(false);
		HitRope();
		m_PlayersHit = true;
		m_HitCooldown = hitcooldown;
	}

	if (m_RecoverSpawner->CheckCollision(players))
	{
		m_CollectSound->Play(0);
		m_RecoverSpawner->Collect();
		m_MaxPlayerDistance += 100;
	}
}

void Game::Draw() const
{
	ClearBackground();

	m_AttackManager->Draw();
	m_RecoverSpawner->Draw();

	DrawPlayers();

	int xWidth{ 0 };
	int yWidth{ 0 };
	const std::string text{ std::to_string(m_Time) };

	TTF_SizeText(m_Font, text.c_str(), &xWidth, &yWidth);
	Rectf viewport{ GetViewPort() };
	Point2f position{ viewport.width,viewport.height };
	Rectf drawRect
	{
		position.x - 100,
		position.y - 100,
		float(xWidth),
		float(yWidth)
	};
	m_TimerText->Draw(position - Vector2f(100,100));

}

void Game::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	//std::cout << "KEYDOWN event: " << e.keysym.sym << std::endl;
	for (int index{ 0 }; index < m_CurrentInput.size(); ++index) {
		if (m_CurrentInput[index] == e.keysym.sym) {
			return;
		}
	}

	m_CurrentInput.push_back(e.keysym.sym);
}

void Game::ProcessKeyUpEvent(const SDL_KeyboardEvent& e)
{
	for (int index{ 0 }; m_CurrentInput.size(); ++index) {
		if (m_CurrentInput[index] == e.keysym.sym) {
			m_CurrentInput.erase(std::next(m_CurrentInput.begin(), index));
			return;
		}
	}
}

void Game::ProcessMouseMotionEvent(const SDL_MouseMotionEvent& e)
{
	//std::cout << "MOUSEMOTION event: " << e.x << ", " << e.y << std::endl;
}

void Game::ProcessMouseDownEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONDOWN event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}

}

void Game::ProcessMouseUpEvent(const SDL_MouseButtonEvent& e)
{
	//std::cout << "MOUSEBUTTONUP event: ";
	//switch ( e.button )
	//{
	//case SDL_BUTTON_LEFT:
	//	std::cout << " left button " << std::endl;
	//	break;
	//case SDL_BUTTON_RIGHT:
	//	std::cout << " right button " << std::endl;
	//	break;
	//case SDL_BUTTON_MIDDLE:
	//	std::cout << " middle button " << std::endl;
	//	break;
	//}
}

void Game::ClearBackground() const
{
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
}

void Game::SimulatePlayerMovement(float elapsedSec)
{
	Rectf viewport{ GetViewPort() };
	Rectf left{ -10,0,10,viewport.height };
	Rectf bottom{ 0,-10,viewport.width,10 };
	Rectf right{ viewport.width, 0, 10,viewport.height };
	Rectf top{ 0,viewport.height,viewport.width,10 };

	Point2f futurePlayer1Position = m_Player1Position + m_Player1Direction * m_PlayerSpeed * elapsedSec;
	Point2f futurePlayer2Position = m_Player2Position + m_Player2Direction * m_PlayerSpeed * elapsedSec;


	const Circlef player1{ futurePlayer1Position,playerRadius };
	const Circlef player2{ futurePlayer2Position,playerRadius };

	if (!utils::IsOverlapping(left, player1) && !utils::IsOverlapping(bottom, player1)
		&& !utils::IsOverlapping(right, player1) && !utils::IsOverlapping(top, player1)) {
		m_Player1Position = futurePlayer1Position;
	}

	if (!utils::IsOverlapping(left, player2) && !utils::IsOverlapping(bottom, player2)
		&& !utils::IsOverlapping(right, player2) && !utils::IsOverlapping(top, player2)) {
		m_Player2Position = futurePlayer2Position;
	}


}

void Game::CheckMaxDistance()
{

	const float distance{ utils::GetDistance(m_Player1Position,m_Player2Position) };
	if (distance > m_MaxPlayerDistance)
	{
		Vector2f player1Dir{ m_Player1Position - m_Player2Position };
		player1Dir = player1Dir / player1Dir.Length();
		Vector2f player2Dir{ -player1Dir };
		const Point2f middle{ m_Player1Position + (m_Player2Position - m_Player1Position) * 0.5f };

		m_Player1Position = middle + player1Dir * (m_MaxPlayerDistance * 0.5f * 0.9f);
		m_Player2Position = middle + player2Dir * (m_MaxPlayerDistance * 0.5f * 0.9f);
	}
}

void Game::HitRope()
{
	m_MaxPlayerDistance -= 100;
	m_HitSound->Play(0);
	if (m_MaxPlayerDistance < 100) {
		RestartGame();
	}
}

void Game::CheckInput()
{
	m_Player1Direction = Vector2f{};
	m_Player2Direction = Vector2f{};

	for (int index{ 0 }; index < m_CurrentInput.size(); ++index) {
		if (m_CurrentInput[index] == SDLK_w) m_Player1Direction.y += 1;
		if (m_CurrentInput[index] == SDLK_s) m_Player1Direction.y += -1;
		if (m_CurrentInput[index] == SDLK_d) m_Player1Direction.x += 1;
		if (m_CurrentInput[index] == SDLK_a) m_Player1Direction.x += -1;

		if (m_CurrentInput[index] == SDLK_UP) m_Player2Direction.y += 1;
		if (m_CurrentInput[index] == SDLK_DOWN) m_Player2Direction.y += -1;
		if (m_CurrentInput[index] == SDLK_RIGHT) m_Player2Direction.x += 1;
		if (m_CurrentInput[index] == SDLK_LEFT) m_Player2Direction.x += -1;
	}

}

void Game::RestartGame()
{
	Rectf window{ GetViewPort() };
	m_AttackManager->ClearAttacks();
	m_WaveManager->SelectWave();
	m_MaxPlayerDistance = 800;
	m_Player1Position = Point2f{ Point2f(window.width * 0.5f,window.height * 0.5f) - Vector2f(100,0) };
	m_Player2Position = Point2f{ Point2f(window.width * 0.5f,window.height * 0.5f) + Vector2f(100,0) };
	m_Player1Direction = Vector2f{};
	m_Player2Direction = Vector2f{};
	m_CurrentBulletSpawn = 20;
	m_Time = 0;
	m_Timer = 0;

	UpdateText();
}

void Game::UpdateText()
{
	if (m_TimerText != nullptr) {
		delete m_TimerText;
	}

	std::string newText{ std::to_string(m_Time) };
	m_TimerText = new Texture(newText, m_Font, Color4f{ 1,1,1,1 });
}

void Game::DrawPlayers() const
{
	const float maxLineWidth{ 20.f };
	const float distance{ utils::GetDistance(m_Player1Position,m_Player2Position) };
	float percent{ (distance / m_MaxPlayerDistance) };
	percent = 1.f - percent;

	utils::SetColor(Color4f{ 0,.75f,0.2f,1 });
	utils::DrawLine(m_Player1Position, m_Player2Position, 1.f + (maxLineWidth * percent));

	utils::SetColor(player1Color);
	if (m_PlayersHit)
	{
		utils::SetColor(Color4f::Lerp(player1Color, playerHitColor, sinf((1 - (m_HitCooldown / hitcooldown)) * M_PI) * 0.5f + 0.5f));
	}

	utils::FillEllipse(m_Player1Position, playerRadius, playerRadius);

	utils::SetColor(player2Color);
	if (m_PlayersHit)
	{
		utils::SetColor(Color4f::Lerp(player2Color, playerHitColor, sinf((1 - (m_HitCooldown / hitcooldown)) * M_PI) * 0.5f + 0.5f));
	}
	utils::FillEllipse(m_Player2Position, playerRadius, playerRadius);

}


