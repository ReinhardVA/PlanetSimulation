#pragma once
#include <vector>
#include "CelestialBody.h"
#include "Core/Layer.h"
class SimulationLayer : public Core::Layer
{
private: 
	std::vector<CelestialBody> m_bodies;

public:
	
};

