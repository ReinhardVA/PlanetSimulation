#pragma once
#include <vector>
#include "CelestialBody.h"
#include "Core/Layer.h"
class SimulationLayer : public Core::Layer
{
private: 
	std::vector<CelestialBody> m_bodies;
	float m_time = 0.0f;

public:
	SimulationLayer();
	virtual ~SimulationLayer();

	void OnUpdate(float deltaTime) override;
	void OnRender() override;
};

