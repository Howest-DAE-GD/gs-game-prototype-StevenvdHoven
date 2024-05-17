#pragma once
#include "AttackManager.h"
#include <vector>

#define wave_cooldown 10

class Wave;
class WaveManager
{
public:
	WaveManager(AttackManager* attackMananger);
	~WaveManager();

	void Update(float elapsedSec);
	void SelectWave();


private:
	float m_CurrentTime;
	float m_Cooldown;

	Wave* m_CurrentWave;
	AttackManager* m_AttackManager;
	std::vector<Wave*> m_Waves;
};

