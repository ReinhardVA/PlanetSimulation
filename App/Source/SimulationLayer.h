#pragma once
#include <vector>
#include "Source/Planet.h"

class SimulationLayer
{
private: 
	std::vector<Planet> m_planets;
	Planet m_sun;

public:
	SimulationLayer() : m_sun(1000.0f, 50.0f, 400.0f, 300.0f) {};
	
};

