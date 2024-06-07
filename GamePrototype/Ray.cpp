#include "pch.h"
#include "Ray.h"

Ray::Ray(const Point2f& pos, const Vector2f& dir, std::vector<Color4f> colors):
	m_Position{pos},
	m_Direction{dir},
	m_Timer{ray_default_warning_time},
	m_Colors{colors},
	m_SoundPlayed{false}
{
	Vector2f up{ m_Direction.y, -m_Direction.x };
	Vector2f down{ -up };

	m_OnShootSound = new SoundEffect{ "Audio/laser-zap-90575.mp3" };

	m_Poly = {
		m_Position + up * (ray_default_width * 0.5),
		m_Position + down * (ray_default_width * 0.5),
		m_Position + down * (ray_default_width * 0.5) + m_Direction * ray_default_length,
		m_Position + up * (ray_default_width * 0.5) + m_Direction * ray_default_length,
	};

	m_InnerPoly = {
			m_Position + up * (ray_default_width * 0.3),
			m_Position + down * (ray_default_width * 0.3),
			m_Position + down * (ray_default_width * 0.3) + m_Direction * ray_default_length,
			m_Position + up * (ray_default_width * 0.3) + m_Direction * ray_default_length,
	};
	
	m_CenterPoly = {
			m_Position + up * (ray_default_width * 0.1),
			m_Position + down * (ray_default_width * 0.1),
			m_Position + down * (ray_default_width * 0.1) + m_Direction * ray_default_length,
			m_Position + up * (ray_default_width * 0.1) + m_Direction * ray_default_length,
	};
}

Ray::~Ray()
{
	delete m_OnShootSound;
}

void Ray::Update(float elapsedSec)
{
	m_Timer -= elapsedSec;
	if (m_Timer <= 0 && !m_SoundPlayed)
	{
		m_SoundPlayed = true;
		m_OnShootSound->SetVolume(70);
		m_OnShootSound->Play(0);
		
	}

	if (m_Timer < -0.5f) 
	{
		SetActive(false);
	}
}

void Ray::Draw() const
{
	Vector2f up{ m_Direction.y, -m_Direction.x };
	Vector2f down{ -up };

	
	if (m_Timer <= 0) 
	{
		utils::SetColor(m_Colors[0]);
		utils::FillPolygon(m_Poly);
		utils::SetColor(m_Colors[1]);
		utils::FillPolygon(m_InnerPoly);
		utils::SetColor(m_Colors[2]);
		utils::FillPolygon(m_CenterPoly);
	}
	else 
	{
		utils::SetColor(ray_default_warning_color);
		utils::FillPolygon(m_Poly);
	}
}

bool Ray::CheckCollision(const std::vector<Circlef> players) const
{
	if (m_Timer > 0) {
		return false;
	}

	for (int index{ 0 }; index < players.size(); ++index)
	{
		if (utils::IsOverlapping(m_Poly, players[index])) 
		{
			return true;
		}
	}

	return false;
}
