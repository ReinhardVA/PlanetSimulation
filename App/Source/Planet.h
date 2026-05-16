#pragma once
class Planet
{
public:
	float m_mass;
	float m_radius;
	
	float m_x;
	float m_y;
	
	float m_velocityX = 5.0f;
	float m_velocityY = 5.0f;

	float m_previousX;
	float m_previousY;

	float m_accelerationX;
	float m_accelerationY;

public:
	Planet(float mass, float radius, float x, float y, float velocityX = 0.0f, float velocityY = 0.0f);
	float GetMass() const;
	float GetRadius() const;
	float GetX() const;
	float GetY() const;
	float GetVelocityX() const;
	float GetVelocityY() const;
	float GetPreviousX() const { return m_previousX; }
	float GetPreviousY() const { return m_previousY; }
};

