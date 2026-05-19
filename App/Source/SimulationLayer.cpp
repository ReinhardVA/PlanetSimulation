#include "SimulationLayer.h"
#include <cmath>
#include <SFML/Graphics/CircleShape.hpp>
#include <Core\Renderer\Renderer.h>

SimulationLayer::SimulationLayer()
{
	sf::Vector2f screenSize = Core::Application::Get().GetFrameBufferSize();
	
	float centerX = screenSize.x / 2.0f;
	float centerY = screenSize.y / 2.0f;
	
	m_bodies.push_back({ {centerX, centerY}, {0.0f, 0.0f}, {0.0f, 0.0f}, 10000.0f, sf::Color::Yellow });
	m_bodies.push_back({ {centerX, centerY - 200.0f}, {150.0f, 0.0f}, {0.0f, 0.0f}, 10.0f, sf::Color::Blue });
	m_bodies.push_back({ {centerX + 200.0f, centerY}, {-150.0f, 0.0f}, {0.0f, 0.0f}, 50.0f, sf::Color::Red });
}

SimulationLayer::~SimulationLayer()
{
}

void SimulationLayer::OnUpdate(float deltaTime)
{
	// Physics update
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
