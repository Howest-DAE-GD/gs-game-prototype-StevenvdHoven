#pragma once
#include "Wave.h"
#include "utils.h"

#define wave_circle_spawnrate .25f
#define wave_square_spawnrate .2f
#define screen_center Point2f{1920 * 0.5, 1080 * 0.5}

class CircleWave final : public Wave
{
public:
	CircleWave(float maxTime, AttackManager* attackManager);
	virtual ~CircleWave();

	void Start() override;
	void Update(float elapsedSec) override;

};

class SquareWave final : public Wave
{
public:
	SquareWave(float maxTime, AttackManager* attackManager, bool reverseX = false, bool reverseY = false);
	virtual ~SquareWave();

	void Start() override;
	void Update(float elapsedSec) override;

private:
	bool m_ReverseX;
	bool m_ReverseY;
};

