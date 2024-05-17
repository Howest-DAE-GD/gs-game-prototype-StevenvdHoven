#pragma once

class AttackManager;
class Wave
{
public:
	Wave(float maxTime, AttackManager* attackManager);
	virtual ~Wave();

	virtual void Start();
	virtual void Update(float elapsedSec);

	float GetMaxTime();
	float GetCurrentPercent();
	void SetCurrentPercent(float currentPercent);

protected:
	AttackManager* m_AttackManager;
	float m_CurrentTimer;

private:
	float m_MaxTime;
	float m_CurrentPercent;
};

