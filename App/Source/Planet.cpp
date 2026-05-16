#include "Planet.h"

Planet::Planet(float mass, float radius, float x, float y, float velocityX, float velocityY)
    : m_mass(mass),
    m_radius(radius),
    m_x(x),
    m_y(y),
    m_velocityX(velocityX),
    m_velocityY(velocityY),
    m_previousX(x),
    m_previousY(y),
    m_accelerationX(0.0f),
    m_accelerationY(0.0f)
{
}
float Planet::GetRadius() const
{
	return m_radius;
}

float Planet::GetX() const
{
	return m_x;
}

float Planet::GetY() const
{
	return m_y;
}

float Planet::GetMass() const
{
	return m_mass;
}
float Planet::GetVelocityX() const
{
    return m_velocityX;
}

float Planet::GetVelocityY() const
{
    return m_velocityY;
}