#include "SimulationLayer.h"
#include "Physics.h"
#include "BarnesHut.h"
#include <SFML/Graphics/CircleShape.hpp>
#include <Core\Renderer\Renderer.h>

#include <cmath>
#include <random>
#include <numbers>

#define GravitationalConstant 0.06f

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_real_distribution<float> massDist(1.0f, 100.0f);

float sunMass = 5000000.0f;

SimulationLayer::SimulationLayer() : m_quadtree(0.5f, 1.0f)
{
	sf::Vector2f screenSize = Core::Application::Get().GetFrameBufferSize();
	
	float centerX = screenSize.x / 2.0f;
	float centerY = screenSize.y / 2.0f;

	CelestialBody sun = { {centerX, centerY}, {centerX, centerY},{0.0f, 0.0f}, {0.0f, 0.0f}, sunMass, sf::Color::Yellow };
	//CelestialBody planet1 = { {centerX, centerY - 200.0f}, {centerX, centerY - 200.0f}, {0.0f, 0.0f}, {0.0f, 0.0f}, 10.0f, sf::Color::Blue };
	//CelestialBody planet2 = { {centerX + 200.0f, centerY}, {centerX + 200.0f, centerY}, {0.0f, 0.0f}, {0.0f, 0.0f}, 50.0f, sf::Color::Red };

	m_bodies.push_back(sun);
	//m_bodies.push_back(planet1);
	//m_bodies.push_back(planet2);
	
	for (size_t i = 0; i < 1000; ++i) {
		float angle = (static_cast<float>(i) / 1000.0f) * 2.0f * std::numbers::pi_v<float>;
		float radius = 300.0f + static_cast<float>(i) / 1000.0f * 200.0f;
		
		float posX = centerX + radius * std::cos(angle);
		float posY = centerY + radius * std::sin(angle);
		float orbitalVelocity = std::sqrt(GravitationalConstant * sunMass / radius);
		float velX = -std::sin(angle) * std::sin(angle);
		float velY = std::cos(angle) * std::cos(angle);
		float randomMass = massDist(gen);
		CelestialBody body = {
			{posX, posY},
			{posX, posY},
			{velX, velY},
			{0.0f, 0.0f},
			randomMass,
			sf::Color::Green
		};
		m_bodies.push_back(body);
	};
	Physics::SetCircularOrbit(m_bodies, sun, GravitationalConstant);
	//Physics::CalculateGravitationalForces(m_bodies, GravitationalConstant);
	Physics::InitializeVerlet(m_bodies, 0.016f); // Assuming 60 FPS
	

}

SimulationLayer::~SimulationLayer()
{
}

void SimulationLayer::OnUpdate(float deltaTime)
{
	BarnesHutImplemantation();

	// Physics update
	//Physics::CalculateGravitationalForces(m_bodies, GravitationalConstant);
	
	//Physics::EulerIntegrate(m_bodies, deltaTime);

	Physics::VerletIntegrate(m_bodies, deltaTime);

}

void SimulationLayer::BarnesHutImplemantation()
{
	BarnesHut::Quad currentSpace = BarnesHut::Quad::CreateFromBounds(m_bodies);
	m_quadtree.clear(currentSpace);
	for (const auto& body : m_bodies) {
		m_quadtree.insert(body.position, body.mass);
	}
	m_quadtree.propagate();
	for (auto& body : m_bodies) {
		sf::Vector2f gravitationalAcceleration = m_quadtree.acceleration(body.position);
		body.acceleration = gravitationalAcceleration * GravitationalConstant;
	}
}

void SimulationLayer::OnRender()
{
	for (const CelestialBody& body : m_bodies) {

		float radius = std::max(5.0f, std::log10(body.mass) * 3.0f);

		sf::CircleShape shape(radius);
		shape.setOrigin({radius, radius});
		shape.setPosition({ body.position.x, body.position.y });
		shape.setFillColor(body.color);

		Renderer::Draw(shape);

	}
}
