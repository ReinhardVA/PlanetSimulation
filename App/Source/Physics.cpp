#include "Physics.h"
#include <cmath>

void Physics::CalculateGravitationalForces(std::vector<CelestialBody>& bodies, float G)
{
	for (auto& body : bodies) {
		body.acceleration = { 0.0f, 0.0f };
	}
	
	for (size_t i = 0; i < bodies.size(); ++i) {
		for (size_t j = 0; j < bodies.size(); j++) {
			if (i == j) continue;

			sf::Vector2f direction = bodies[j].position - bodies[i].position;
			float distanceSquared = direction.x * direction.x + direction.y * direction.y + 0.0001f;
			float distance = std::sqrt(distanceSquared);

			float accelerationMagnitude = G * bodies[j].mass / (distanceSquared * distance); // w^2 = G * M / r^3
			bodies[i].acceleration += direction * accelerationMagnitude; // a = w^2 * r 
		}
	}
}

void Physics::SetCircularOrbit(std::vector<CelestialBody>& bodies, const CelestialBody& centralBody, float G)
{
	for (size_t i = 0; i < bodies.size(); ++i) {
 		const float dx = centralBody.position.x - bodies[i].position.x;
		const float dy = centralBody.position.y - bodies[i].position.y;
		const float r = std::sqrt(dx * dx + dy * dy);
		if (r < 0.0001f) 
			continue;
		const float circularSpeed = std::sqrt(G * centralBody.mass / r);
		bodies[i].velocity.x = -dy / r * circularSpeed;
		bodies[i].velocity.y = dx / r * circularSpeed;
	}
}

void Physics::EulerIntegrate(std::vector<CelestialBody>& bodies, float deltaTime)
{
	for (size_t i = 0; i < bodies.size(); ++i) {
		bodies[i].velocity += bodies[i].acceleration * deltaTime;
		bodies[i].position += bodies[i].velocity * deltaTime;
	}
}

void Physics::InitializeVerlet(std::vector<CelestialBody>& bodies, float deltaTime)
{
	for (auto& body : bodies) {
		body.previousPosition = body.position - (body.velocity * deltaTime) + 0.5f * body.acceleration * deltaTime * deltaTime;
	}
}

void Physics::VerletIntegrate(std::vector<CelestialBody>& bodies, float deltaTime)
{
	for (size_t i = 0; i < bodies.size(); ++i) {
		sf::Vector2f newPosition = 2.0f * bodies[i].position - bodies[i].previousPosition + bodies[i].acceleration * deltaTime * deltaTime;
		bodies[i].previousPosition = bodies[i].position;
		bodies[i].position = newPosition;
	}
}

