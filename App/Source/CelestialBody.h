#pragma once
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Color.hpp>
struct CelestialBody
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f acceleration;
	float mass;
	sf::Color color;
};

