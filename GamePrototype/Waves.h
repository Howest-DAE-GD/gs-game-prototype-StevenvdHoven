#pragma once
#include "Wave.h"
#include "utils.h"
#include <vector>


#define wave_circle_spawnrate .1f
#define wave_square_spawnrate .5f
#define wave_square_ray_spawnrate 0.10f
#define screen_center Point2f{1920 * 0.5, 1080 * 0.5}

class Ray;
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

class BothSquareWave final : public Wave
{
public:
	BothSquareWave(float maxTime, AttackManager* attackManager, float spawnRate);

	void Start() override;
	void Update(float elapsedSec) override;

private:
	float m_SpawnRate;
	float m_Timer;
};

class SquareWaveRay final : public Wave
{
public:
	SquareWaveRay(float maxTime, AttackManager* attackManager, bool reverseX = false, bool reverseY = false);
	virtual ~SquareWaveRay();

	void Start() override;
	void Update(float elapsedSec) override;

private:
	void GenerateAttacks();

	bool m_ReverseX;
	bool m_ReverseY;

	int m_AttackIndex;
	std::vector<Ray*> m_Attacks;
};

class JailWaveRay final : public Wave
{
public:
	JailWaveRay(float maxTime, AttackManager* attackManager, int spacing, int width);
	virtual ~JailWaveRay();

	void Start() override;
	void Update(float elapsedSec) override;

private:
	int m_Spacing;
	int m_Width;
};

