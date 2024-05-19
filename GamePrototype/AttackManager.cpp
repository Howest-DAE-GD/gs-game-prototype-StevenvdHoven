#include "pch.h"
#include "AttackManager.h"
#include "Attack.h"

AttackManager::AttackManager()
{
}

AttackManager::~AttackManager()
{
	ClearAttacks();
}

void AttackManager::Update(float elapsedSec)
{
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		if (m_Attacks[index]->IsActive()) 
		{
			m_Attacks[index]->Update(elapsedSec);
		}
			
	}
}

void AttackManager::Draw() const
{
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		if (m_Attacks[index]->IsActive())
		{
			m_Attacks[index]->Draw();
		}
	}
}

void AttackManager::AddAttack(Attack* attack)
{
	m_Attacks.push_back(attack);
}

void AttackManager::DeleteAttack(Attack* attack)
{
	std::vector<Attack*> attacks;
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		if (m_Attacks[index] == attack)
		{
			delete m_Attacks[index];
			m_Attacks[index] = nullptr;
		}
		else
		{
			attacks.push_back(m_Attacks[index]);
		}
	}
	m_Attacks = std::move(attacks);
}

void AttackManager::ClearAttacks()
{
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		delete m_Attacks[index];
	}
	m_Attacks.clear();
}

Attack* AttackManager::CheckCollisionAttacks(const std::vector<Circlef> players)
{
	for (int index{ 0 }; index < m_Attacks.size(); ++index)
	{
		if (m_Attacks[index]->CheckCollision(players) && m_Attacks[index]->IsActive())
		{
			return m_Attacks[index];
		}
	}

	return nullptr;
}
