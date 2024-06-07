#pragma once
#include "AttackManager.h"
#include <vector>

#define wave_cooldown 5

class Wave;
class WaveManager
{
public:
	WaveManager(AttackManager* attackMananger);
	~WaveManager();

	void Update(float elapsedSec);
	void SelectWave();

	int GetWaves();

private:
	float m_CurrentTime;
	float m_Cooldown;
	int m_AmoutOfWaves;

	Wave* m_CurrentWave;
	AttackManager* m_AttackManager;
	std::vector<Wave*> m_Waves;
};

