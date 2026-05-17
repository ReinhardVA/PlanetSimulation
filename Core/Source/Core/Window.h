#pragma once
#include <string>
#include <SFML/Graphics.hpp>

namespace Core
{
	struct WindowSpecification {
		std::string Title;
		uint32_t Width = 1280;
		uint32_t Height = 720;
		bool IsResizable = true;
		bool VSync = true;
	};
	class Window
	{
	private:
		WindowSpecification m_specification;
		std::unique_ptr<sf::RenderWindow> m_window;

	public:
		Window(const WindowSpecification& specification = WindowSpecification());
		~Window();

		void Create();
		void Destroy();
		void Update();
		void ProcessEvents();

		sf::Vector2f GetFrameBufferSize() const;

		bool ShouldClose() const;

		sf::RenderWindow* GetHandle() const { return m_window.get(); }
	};

}