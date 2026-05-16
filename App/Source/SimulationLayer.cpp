#include "SimulationLayer.h"

void SimulationLayer::OnAttach()
{
	Planet planet1(10.0f, 20.0f, 100.0f, 100.0f);
	m_planets.push_back(planet1);
}

void SimulationLayer::OnUpdate(float deltaTime)
{

}

void SimulationLayer::OnRender(Renderer& renderer)
{
	renderer.Draw(m_planets, m_sun);
}
