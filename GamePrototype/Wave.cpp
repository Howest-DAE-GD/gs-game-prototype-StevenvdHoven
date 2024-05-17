#include "pch.h"
#include "Wave.h"



Wave::Wave(float maxTime, AttackManager* attackManager):
	m_MaxTime{ maxTime },
	m_CurrentPercent{ 0 },
	m_AttackManager{ attackManager },
	m_CurrentTimer{0}
{
}

Wave::~Wave()
{
}

void Wave::Start()
{
}

void Wave::Update(float elapsedSec)
{
}

float Wave::GetMaxTime()
{
	return m_MaxTime;
}

float Wave::GetCurrentPercent()
{
	return m_CurrentPercent;
}

void Wave::SetCurrentPercent(float currentPercent)
{
	m_CurrentPercent = currentPercent;
}
