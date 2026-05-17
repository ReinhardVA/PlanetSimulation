#pragma once
#include "Renderer/Renderer.h"
#include "Window.h"
#include "Layer.h"
namespace Core
{
	struct ApplicationSpecification {
		std::string Name = "Solar System Simulation";
	};
	class Application
	{
		ApplicationSpecification m_specification;
		std::shared_ptr<Window> m_window;
		bool m_running = true;
		static sf::Clock s_timer;

		std::vector<std::unique_ptr<Layer>> m_layerStack;

		friend class Layer;

	public:
		Application(const ApplicationSpecification& specification = ApplicationSpecification());
		~Application();

		void Run();
		void Stop();

		template<typename TLayer>
			requires(std::is_base_of_v<Layer, TLayer>)
		void PushLayer() {
			m_layerStack.push_back(std::make_unique<Layer>());
		}

		template<typename TLayer>
			requires(std::is_base_of_v<Layer, TLayer>)
		TLayer* GetLayer() {
			for (const auto& layer : m_layerStack) {
				if (auto casted = dynamic_cast<TLayer*>(layer.get())) {
					return casted;
				}
			}
			return nullptr;
		}

		std::shared_ptr<Window> GetWindow() const { return m_window; }

		sf::Vector2f GetFrameBufferSize() const;

		static Application& Get();
		static float GetTime();

		//void EulerIntegrate(float deltaTime, std::vector<Planet>& planets, Planet& sun);
	};

}