#pragma once
#include <vector>
class AttackManager;
class Attack
{
	public:
		Attack();
		virtual ~Attack();

		virtual void Update(float elapsedSec);
		virtual void Draw() const;
		virtual bool CheckCollision(const std::vector<Circlef> players) const;

		bool IsActive();
		void SetActive(bool active);

		void AddAttack(Attack* attack);

private:
	bool m_Active;
	AttackManager* m_Manager;
};

