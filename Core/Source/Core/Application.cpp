#include "Application.h"
#include <cassert>
#include "Renderer/Renderer.h"

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
	
}