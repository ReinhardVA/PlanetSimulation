#include "Application.h"
#include <cassert>
#include "Renderer/Renderer.h"
#include <iostream>
namespace Core
{

	static Application* s_Application = nullptr;
	sf::Clock Application::s_timer;


	Application::Application(const ApplicationSpecification& specification)
		: m_specification(specification)
	{
		s_Application = this;
		
		if (m_specification.WindowSpec.Title.empty())
			m_specification.WindowSpec.Title = m_specification.Name;

		m_window = std::make_shared<Window>(m_specification.WindowSpec);
		m_window->Create();
	}

	Application::~Application()
	{
		m_window->Destroy();
		s_Application = nullptr;
	}

	void Application::Run()
	{
		sf::Clock frameClock;
		m_running = true;
		while (m_running) {

			m_window->ProcessEvents(); // A.Process/Poll Events -> close window, resize, etc.

			if (m_window->ShouldClose()) {
				Stop();
				break;
			}
			const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.1f);

			// Main Layer Update
			for (const std::unique_ptr<Layer>& layer : m_layerStack) { // B. Update -> update game logic, physics, etc.
				layer->OnUpdate(deltaTime);
			}

			// C. Render -> clear screen, draw, display

			Renderer::Clear();
			
			for (const std::unique_ptr<Layer>& layer : m_layerStack) {
				layer->OnRender();
			}

			m_window->Update(); // display
		}

		// Clear screen
		// Draw
		// Display

		// Main application loop
		//while (m_running)
		//{
		//	const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.033f);
			//m_renderer.PollEvents();
			//m_renderer.Clear();
			//for (auto& layer : m_layerStack)
			//{
			//	layer->OnUpdate(deltaTime);
			//	layer->OnRender(m_renderer);
			//}
			//m_renderer.Display();
		//}
		//Planet planet1(10.0f, 20.0f, 100.0f, 100.0f);
		//Planet sun(1000.0f, 50.0f, 400.0f, 300.0f);
		//std::vector<Planet> planets = { planet1 };
		//const float G = 30000;
		//const float dx = sun.m_x - planet1.m_x;
		//const float dy = sun.m_y - planet1.m_y;
		//const float r = sqrt(dx * dx + dy * dy);
		//const float circularSpeed = sqrt(G * sun.m_mass / r);

		//planets[0].m_velocityX = -dy / r * circularSpeed;
		//planets[0].m_velocityY = dx / r * circularSpeed;
		//sf::Clock frameClock;
		//while (m_renderer.IsOpen())
		//{
		//	const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.033f);
		//	m_renderer.PollEvents();
		//	m_renderer.Clear();
		//	EulerIntegrate(deltaTime, planets, sun);
		//	m_renderer.Draw(planets, sun);
		//	m_renderer.Display();
		//}
	}

	void Application::Stop()
	{
		m_running = false;
	}

	sf::Vector2f Application::GetFrameBufferSize() const
	{
		return m_window->GetFrameBufferSize();
	}

	Application& Application::Get()
	{
		assert(s_Application);
		return *s_Application;
	}
	float Application::GetTime()
	{
		return s_timer.getElapsedTime().asSeconds();
	}
	//void Application::EulerIntegrate(float deltaTime, std::vector<Planet>& planets, Planet& sun)
	//{
	//	double G = 30000;
	//	float dx = sun.m_x - planets[0].m_x;
	//	float dy = sun.m_y - planets[0].m_y;
	//	float distancesq = dx * dx + dy * dy + 0.0001f;
	//	float distance = sqrt(distancesq);

	//	float accelFator = G * sun.m_mass / (distance * distancesq);
	//	float accelerationX = accelFator * dx;
	//	float accelerationY = accelFator * dy;

	//	// Update Velocity
	//	planets[0].m_velocityX += accelerationX * deltaTime;
	//	planets[0].m_velocityY += accelerationY * deltaTime;
	//	// Store Previous Position
	//	planets[0].m_previousX = planets[0].m_x;
	//	planets[0].m_previousY = planets[0].m_y;
	//	// Update Position
	//	planets[0].m_x = planets[0].m_previousX + planets[0].m_velocityX * deltaTime;
	//	planets[0].m_y = planets[0].m_previousY + planets[0].m_velocityY * deltaTime;

	//}
}