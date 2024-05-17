#pragma once
#include <vector>

class Attack;
class AttackManager
{
public:
	AttackManager();

	void Update(float elapsedSec);
	void Draw() const;

	void AddAttack(Attack* attack);
	void DeleteAttack(Attack* attack);
	void ClearAttacks();

	Attack* CheckCollisionAttacks(const std::vector<const Circlef&> players);

private:
	std::vector<Attack*> m_Attacks;
};

