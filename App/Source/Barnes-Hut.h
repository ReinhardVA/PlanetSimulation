#pragma once
#include <SFML/System/Vector2.hpp>
#include <vector>
#include "CelestialBody.h"

namespace BarnesHut
{
	struct Quad {
		sf::Vector2f center;
		float size;

		static Quad CreateFromBounds(const std::vector<CelestialBody>& bodies);
		size_t findQuadrant(sf::Vector2f position) const;
		Quad intoQuadrant(size_t quadrant);
		std::vector<Quad> subdivide() const;
	};

	struct Node {
		size_t children = 0;
		size_t next = 0;
		sf::Vector2f position{ 0.0f, 0.0f };
		float mass = 0.0f;
		Quad quad;

		Node(size_t next, Quad quad) : next(next), quad(quad) {}

		bool isLeaf() const {
			return children == 0;
		}

		bool isBranch() const {
			return children != 0;
		}

		bool isEmpty() const {
			return mass == 0.0f;
		}
	};

	class Quadtree {
	private:
		
		float theta;
		float epsilon;

		size_t subdivide(size_t index);

	public:
		const size_t ROOT = 0;

		std::vector<Node> nodes;
		std::vector<size_t> parents;

		Quadtree(float theta, float epsilon);

		void clear();
		void insert(sf::Vector2f position, float mass);
		void propagate();
		sf::Vector2f acceleration(sf::Vector2f position) const;
	};
}
