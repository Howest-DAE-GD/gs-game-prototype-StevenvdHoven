#include "pch.h"
#include "Waves.h"
#include "Bullet.h"
#include "AttackManager.h"

CircleWave::CircleWave(float maxTime,AttackManager* attackManager):
	Wave(maxTime, attackManager)
{
}

CircleWave::~CircleWave()
{
}

void CircleWave::Start()
{
}

void CircleWave::Update(float elapsedSec)
{
	if (m_CurrentTimer <= 0) 
	{
		m_CurrentTimer = wave_circle_spawnrate;
		float angle{ 360 * GetCurrentPercent() };

		float x{ cosf(angle) * 1000 };
		float y{ sinf(angle) * 1000 };

		Point2f pos{ Point2f{x,y} + Vector2f{1920 * 0.5f,1080 * 0.5f} };
		Vector2f dir{ screen_center - pos };
		dir = dir / dir.Length();

		Bullet* bullet{ new Bullet{pos,dir} };
		m_AttackManager->AddAttack(bullet);
	}
	else 
	{
		m_CurrentTimer -= elapsedSec;
	}
}

SquareWave::SquareWave(float maxTime, AttackManager* attackManager, bool reverseX, bool reverseY):
	Wave(maxTime, attackManager),
	m_ReverseX{ reverseX },
	m_ReverseY{ reverseY }
{
}

SquareWave::~SquareWave()
{
}

void SquareWave::Start()
{
}

void SquareWave::Update(float elapsedSec)
{
	if (m_CurrentTimer <= 0) 
	{
		m_CurrentTimer = wave_square_spawnrate;
		
		const float maxX{ 1920 };
		float x = -bullet_default_radius;
		if (!m_ReverseX) x = maxX * GetCurrentPercent();
		else x = (1920 + bullet_default_radius) - maxX * GetCurrentPercent();

		float y = 1080 + bullet_default_radius;
		if (m_ReverseY) y = -bullet_default_radius;

		Point2f pos{ x, y };
		Vector2f dir{ screen_center - pos };
		dir = dir / dir.Length();

		Bullet* bullet{ new Bullet{pos, dir} };
		m_AttackManager->AddAttack(bullet);

	}
	else
	{
		m_CurrentTimer -= elapsedSec;
	}
}
