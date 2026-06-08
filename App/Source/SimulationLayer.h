#pragma once
#include <vector>
#include "CelestialBody.h"
#include "Core/Layer.h"
#include "BarnesHut.h"
class SimulationLayer : public Core::Layer
{
private: 
	std::vector<CelestialBody> m_bodies;
	BarnesHut::Quadtree m_quadtree;
	float m_time = 0.0f;

public:
	SimulationLayer();
	virtual ~SimulationLayer();

	void OnUpdate(float deltaTime) override;
	void BarnesHutImplemantation();
	void OnRender() override;
};

