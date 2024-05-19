#include "pch.h"
#include "WaveManager.h"
#include "Wave.h"
#include "Waves.h"

WaveManager::WaveManager(AttackManager* attackMananger) :
	m_CurrentTime{ 0 },
	m_Cooldown{ wave_cooldown },
	m_CurrentWave{ nullptr },
	m_AttackManager{ attackMananger }
{
	m_Waves = std::vector<Wave*>
	{
		new CircleWave(10, attackMananger),
		new SquareWave(10, attackMananger),
		new SquareWave(10, attackMananger, true),
		new SquareWave(10, attackMananger, true, true),
		new SquareWave(10, attackMananger, false, true)
	};

	SelectWave();
}

WaveManager::~WaveManager()
{
	for (int index{ 0 }; index < m_Waves.size(); ++index)
	{
		delete m_Waves[index];
	}
}

void WaveManager::Update(float elapsedSec)
{
	if (m_CurrentTime >= m_CurrentWave->GetMaxTime())
	{
		if (m_Cooldown <= 0)
		{
			m_Cooldown = wave_cooldown;
			SelectWave();
		}
		else
		{
			m_Cooldown -= elapsedSec;
		}

	}
	else
	{
		m_CurrentTime += elapsedSec;
		const float percent{ m_CurrentTime / m_CurrentWave->GetMaxTime() };
		m_CurrentWave->SetCurrentPercent(percent);
		m_CurrentWave->Update(elapsedSec);
	}
}

	

void WaveManager::SelectWave()
{
	int rand{ int(std::rand() % m_Waves.size()) };

	m_CurrentWave = m_Waves[rand];
	m_AttackManager->ClearAttacks();
	m_CurrentWave->Start();
	m_CurrentTime = 0;
}
