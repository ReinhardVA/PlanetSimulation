#include "Barnes-Hut.h"
#include <cmath>

namespace BarnesHut
{
	Quad Quad::CreateFromBounds(const std::vector<CelestialBody>& bodies)
	{
		float minX = std::numeric_limits<float>::max();
		float minY = std::numeric_limits<float>::max();
		float maxX = std::numeric_limits<float>::lowest();
		float maxY = std::numeric_limits<float>::lowest();

		for (const auto& body : bodies) {
			minX = std::min(minX, body.position.x);
			minY = std::min(minY, body.position.y);
			maxX = std::max(maxX, body.position.x);
			maxY = std::max(maxY, body.position.y);
		}

		sf::Vector2f center = sf::Vector2f(minX + maxX, minY + maxY) * 0.5f;
		float size = std::max(maxX - minX, maxY - minY);
		return Quad{ center, size };
	}

	size_t Quad::findQuadrant(sf::Vector2f position) const
	{
		return (static_cast<size_t>(position.y > center.y) << 1) | static_cast<size_t>(position.x > center.x);
	}

	Quad Quad::intoQuadrant(size_t quadrant)
	{
		size *= 0.5f;
		center.x += (static_cast<float>(quadrant & 1) - 0.5f) * size;
		center.y += (static_cast<float>(quadrant >> 1) - 0.5f) * size;
		return *this;
	}

	std::vector<Quad> Quad::subdivide() const
	{
		return{
			Quad(*this).intoQuadrant(0),
			Quad(*this).intoQuadrant(1),
			Quad(*this).intoQuadrant(2),
			Quad(*this).intoQuadrant(3)
		};
	}

	size_t Quadtree::subdivide(size_t index)
	{
		parents.push_back(index);
		size_t childIndex = nodes.size();
		nodes[index].children = childIndex;

		size_t next[4] = {
			childIndex + 1,
			childIndex + 2,
			childIndex + 3,
			nodes[index].next
		};

		std::vector<Quad> quads = nodes[index].quad.subdivide();

		for (size_t i = 0; i < 4; ++i) {
			nodes.emplace_back(next[i], quads[i]);
		}

		return childIndex;
	}

	void Quadtree::insert(sf::Vector2f position, float mass)
	{
		size_t nodeIndex = ROOT;

		while (nodes[nodeIndex].isBranch()) {
			size_t quadrant = nodes[nodeIndex].quad.findQuadrant(position);
			nodeIndex = nodes[nodeIndex].children + quadrant;
		}

		if (nodes[nodeIndex].isEmpty()) {
			nodes[nodeIndex].position = position;
			nodes[nodeIndex].mass = mass;
			return;
		}

		sf::Vector2f oldPosition = nodes[nodeIndex].position;
		float oldMass = nodes[nodeIndex].mass;

		if (position == oldPosition) {
			nodes[nodeIndex].mass += mass;
			return;
		}

		while (true) {
			size_t childrenStart = subdivide(nodeIndex);

			size_t q1 = nodes[nodeIndex].quad.findQuadrant(oldPosition);
			size_t q2 = nodes[nodeIndex].quad.findQuadrant(position);

			if (q1 == q2) {
				nodeIndex = childrenStart + q1;
			}
			else {
				size_t n1 = childrenStart + q1;
				size_t n2 = childrenStart + q2;

				nodes[n1].position = oldPosition;
				nodes[n1].mass = oldMass;

				nodes[n2].position = position;
				nodes[n2].mass = mass;

				return;
			}
		}
	}

	void Quadtree::propagate()
	{
		for (auto it = parents.rbegin(); it != parents.rend(); ++it) {
			
			size_t nodeIndex = *it;
			
			size_t i = nodes[nodeIndex].children;

			nodes[nodeIndex].position = 
				nodes[i].position * nodes[i].mass +
				nodes[i + 1].position * nodes[i + 1].mass +
				nodes[i + 2].position * nodes[i + 2].mass +
				nodes[i + 3].position * nodes[i + 3].mass;
			
			nodes[nodeIndex].mass = nodes[i].mass +
				nodes[i + 1].mass +
				nodes[i + 2].mass +
				nodes[i + 3].mass;

			float totalMass = nodes[nodeIndex].mass;

			if (totalMass > 0.0f) {
				nodes[nodeIndex].position /= totalMass;
			}
		}
	}

	sf::Vector2f Quadtree::acceleration(sf::Vector2f position) const
	{
		sf::Vector2f totalAcceleration{ 0.0f, 0.0f };
		size_t nodeIndex = ROOT;

		while (true) {
			const Node& node = nodes[nodeIndex];
			sf::Vector2f distance = node.position - position;
			float distanceSquared = distance.x * distance.x + distance.y * distance.y;

			if (node.isLeaf() || (node.quad.size * node.quad.size < distanceSquared * theta * theta)) {
				if (distanceSquared > 0.0f) {
					float denom = (distanceSquared + epsilon * epsilon) * std::sqrt(distanceSquared);
					float m_over_denom = std::min(node.mass / denom, std::numeric_limits<float>::max());
					totalAcceleration += distance * m_over_denom;
				}

				if (node.next == 0) {
					break;
				}

				nodeIndex = node.next;
			}
			else
				nodeIndex = node.children;
		}

		return totalAcceleration;
	}


}