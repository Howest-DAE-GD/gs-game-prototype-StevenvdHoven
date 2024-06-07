#include "pch.h"
#include "Waves.h"
#include "Bullet.h"
#include "Ray.h"
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
		angle = angle * (float(M_PI) / 180.f);

		float x{ cosf(angle) * 1000 };
		float y{ sinf(angle) * 1000 };

		Point2f pos{ Point2f{1920 * 0.5f,1080 * 0.5f} + Vector2f{x,y} };
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
		Vector2f dir{ 0,-1 };
		if (m_ReverseY) dir.y = 1;

		dir = dir / dir.Length();

		Bullet* bullet{ new Bullet{pos, dir} };
		m_AttackManager->AddAttack(bullet);

	}
	else
	{
		m_CurrentTimer -= elapsedSec;
	}
}

SquareWaveRay::SquareWaveRay(float maxTime, AttackManager* attackManager, bool reverseX, bool reverseY):
	Wave(maxTime, attackManager),
	m_ReverseX{ reverseX },
	m_ReverseY{ reverseY },
	m_AttackIndex{0}
{
}

SquareWaveRay::~SquareWaveRay()
{
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		if (m_Attacks[index] != nullptr)
		{
			delete m_Attacks[index];
		}
	}
	m_Attacks.clear();
}

void SquareWaveRay::Start()
{
	GenerateAttacks();
}

void SquareWaveRay::Update(float elapsedSec)
{
	float elapsedTime{ GetCurrentPercent() - m_lastPercent };
	if (elapsedTime > wave_square_ray_spawnrate)
	{
		if (m_AttackIndex < m_Attacks.size()) {
			m_AttackManager->AddAttack(m_Attacks[m_AttackIndex]);
			m_Attacks[m_AttackIndex] = nullptr;
			++m_AttackIndex;
		}
		m_lastPercent = GetCurrentPercent();
	}
}

void SquareWaveRay::GenerateAttacks()
{
	std::vector<Color4f> colors
	{
		Color4f{1,0,0,1},
		Color4f{0.8f,0.2f,0,1},
		Color4f{0.5f,0.5f,0,1},
	};

	int amount{ 1920 / ray_default_width };
	if (m_ReverseY)
		amount = 1080 / ray_default_width + 1;
	std::vector<Ray*> attacks;

	for (int index{ 0 }; index < amount; ++index) 
	{
		float x = (ray_default_width * 0.5f) + ray_default_width * index;
		if (m_ReverseX) x = 1920 - ((ray_default_width * 0.5f) + ray_default_width * index);
		if (m_ReverseY) x = 0;

		float y = 1920;
		if (m_ReverseY) y = (ray_default_width * 0.5f) + ray_default_width * index;

		Point2f pos{ x, y };
		Vector2f dir{ 0,-1 };
		if (m_ReverseY) dir = Vector2f{1, 0 };

		attacks.push_back(new Ray{pos,dir,colors});
	}

	m_Attacks = attacks;
}

BothSquareWave::BothSquareWave(float maxTime, AttackManager* attackManager, float spawnRate) :
	Wave(maxTime, attackManager),
	m_SpawnRate{spawnRate},
	m_Timer{ -1 }
{
}

void BothSquareWave::Start()
{
	
}

void BothSquareWave::Update(float elapsedSec)
{
	m_Timer -= elapsedSec;
	if (m_Timer < 0)
	{
		m_Timer = m_SpawnRate;

		for (int index{ 0 }; index < 10; ++index)
		{
			Point2f pos{ 1920.f * float(index / 10.f),1100 };
			Vector2f dir{ 0,-1 };
			Bullet* bullet{ new Bullet{pos,dir} };
			m_AttackManager->AddAttack(bullet);
		}

		for (int index{ 0 }; index < 10; ++index)
		{
			Point2f pos{ 50 + 1920.f * float(index / 10.f),-100 };
			Vector2f dir{ 0,1 };
			Bullet* bullet{ new Bullet{pos,dir} };
			m_AttackManager->AddAttack(bullet);
		}
	}
}

JailWaveRay::JailWaveRay(float maxTime, AttackManager* attackManager, int spacing, int width):
	Wave(maxTime,attackManager),
	m_Spacing{spacing},
	m_Width{width}
{
}

JailWaveRay::~JailWaveRay()
{
}

void JailWaveRay::Start()
{
	int amount{ 1920 / int(m_Width + m_Spacing * 0.5f) };

	std::vector<Color4f> colors
	{
		Color4f{1,0,0,1},
		Color4f{0.8f,0.2f,0,1},
		Color4f{0.5f,0.5f,0,1},
	};

	float x{ m_Width*0.5f };
	for (int index{ 0 }; index < amount; ++index)
	{
		Point2f pos{x,1090};
		Ray* ray{ new Ray{pos,Vector2f{0,-1},colors,float(m_Width)} };
		m_AttackManager->AddAttack(ray);

		x += m_Width + m_Spacing;
	}

}

void JailWaveRay::Update(float elapsedSec)
{
}
