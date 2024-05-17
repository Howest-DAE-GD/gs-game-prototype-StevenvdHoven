#include "pch.h"
#include "Attack.h"
#include "AttackManager.h"

Attack::Attack():
	m_Active{false}
{
}

Attack::~Attack()
{
}

void Attack::Update(float elapsedSec)
{
}

void Attack::Draw() const
{
}

bool Attack::CheckCollision(const std::vector<Circlef> players) const
{
	return false;
}

bool Attack::IsActive()
{
	return m_Active;
}

void Attack::SetActive(bool active)
{
	m_Active = active;
}

void Attack::AddAttack(Attack* attack)
{
	m_Manager->AddAttack(attack);
}
