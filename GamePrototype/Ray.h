#pragma once
#include "Attack.h"
#include "utils.h"
#include "SoundEffect.h"

#define ray_default_warning_color Color4f{1,1,0,1.f}
#define ray_default_warning_time 1.5f

#define ray_default_width 192
#define ray_default_length 1920

class Ray final : public Attack
{
public:
	Ray(const Point2f& pos, const Vector2f& dir, std::vector<Color4f> colors, float width = ray_default_width);
	virtual ~Ray();

	void Update(float elapsedSec) override;
	void Draw() const override;
	bool CheckCollision(const std::vector<Circlef> players) const override;

private:
	Point2f m_Position;
	Vector2f m_Direction;

	float m_Timer;
	float m_Width;


	std::vector<Color4f> m_Colors;

	std::vector<Point2f> m_Poly;
	std::vector<Point2f> m_InnerPoly;
	std::vector<Point2f> m_CenterPoly;

	SoundEffect* m_OnShootSound;
	bool m_SoundPlayed;
};

