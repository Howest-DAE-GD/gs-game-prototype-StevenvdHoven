#pragma once
#include "Attack.h"
#include "utils.h"

#define color_red Color4f{1,0,0,1}
#define bullet_default_radius 10
#define bullet_defualt_speed 360.f

class Bullet : public Attack
{
public:
	Bullet(const Point2f& pos, const Vector2f& dir, const Color4f& color = color_red);
	virtual ~Bullet();

	void Update(float elapsedSec) override;
	void Draw() const override;
	bool CheckCollision(const std::vector<Circlef> players) const override;

private:
	Point2f m_Position;
	Vector2f m_Direction;
	Color4f m_Color;
};

