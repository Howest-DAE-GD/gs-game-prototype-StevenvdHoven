#include "pch.h"
#include "RecoverSpawner.h"

#include "RecoverSpawner.h"

RecoverSpawner::RecoverSpawner() :
	m_RecoverPosition{},
	m_Timer{ recover_ball_timer },
	m_Activated{ false }
{
}

void RecoverSpawner::Update(float elpasedSec, float lineLength)
{
	if (lineLength < 800)
	{
		if (!m_Activated)
		{
			if (m_Timer < 0)
			{

				m_Activated = true;
				Point2f pos
				{
					recover_ball_radius + float(rand() % (1921 - recover_ball_radius * 2)),
					recover_ball_radius + float(rand() % (1080 - recover_ball_radius * 2))
				};
				m_RecoverPosition = pos;
			}
			else
			{
				m_Timer -= elpasedSec;
			}
		}
	}
}

void RecoverSpawner::Draw() const
{
	if (!m_Activated)
	{
		return;
	}

	utils::SetColor(Color4f{ 0,1,0,1 });
	utils::FillEllipse(m_RecoverPosition, recover_ball_radius, recover_ball_radius);
}

bool RecoverSpawner::CheckCollision(const std::vector<Circlef> players)
{
	if (!m_Activated)
	{
		return false;
	}

	const Circlef recoverCircle{ m_RecoverPosition,recover_ball_radius };
	for (int index{ 0 }; index < players.size(); ++index)
	{
		if (utils::IsOverlapping(recoverCircle, players[index]))
		{
			return true;
		}
	}

	return false;
}

void RecoverSpawner::Collect()
{
	m_Activated = false;
	m_Timer = recover_ball_timer;
}
