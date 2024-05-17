#include "pch.h"
#include "Bullet.h"

Bullet::Bullet(const Point2f& pos, const Vector2f& dir, const Color4f& color):
	m_Position{ pos },
	m_Direction{ dir },
	m_Color{ color }
{
}

Bullet::~Bullet()
{
}

void Bullet::Update(float elapsedSec)
{
	m_Position += m_Direction * bullet_defualt_speed * elapsedSec;
}

void Bullet::Draw() const
{
	utils::SetColor(m_Color);
	const Ellipsef ellipse{ m_Position,bullet_default_radius,bullet_default_radius };
	utils::FillEllipse(ellipse);
}

bool Bullet::CheckCollision(const std::vector<const Circlef&> players) const
{
	const Circlef selfCollider{ m_Position,bullet_default_radius };
	for (int index{ 0 }; index < players.size(); ++index)
	{
		if (utils::IsOverlapping(selfCollider, players[index])) 
		{
			return true;
		}
	}

	return false;
}
