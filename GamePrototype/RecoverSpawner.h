#pragma once
#include "utils.h"

#define recover_ball_radius 50
#define recover_ball_timer 10


class RecoverSpawner
{
public:
	RecoverSpawner();

	void Update(float elpasedSec, float lineLength);
	void Draw() const;

	bool CheckCollision(const std::vector<Circlef> players);
	void Collect();

private:

	Point2f m_RecoverPosition;
	bool m_Activated;
	float m_Timer;
};