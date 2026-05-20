#pragma once
#include <vector>
#include "CelestialBody.h"

namespace Physics {
	void CalculateGravitationalForces(std::vector<CelestialBody>& bodies, float G = 1000.0f);
	
	void SetCircularOrbit(std::vector<CelestialBody>& bodies, const CelestialBody& centralBody, float G = 1000.0f);

	void EulerIntegrate(std::vector<CelestialBody>& bodies, float deltaTime);
	
	void InitializeVerlet(std::vector<CelestialBody>& bodies, float deltaTime);
	
	void VerletIntegrate(std::vector<CelestialBody>& bodies, float deltaTime);
}