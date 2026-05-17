#include "Window.h"
namespace Core
{
	Window::Window(const WindowSpecification& specification) : m_specification(specification) {
	}

	Window::~Window()
	{
		Destroy();
	}

	void Window::Create()
	{
		sf::VideoMode videoMode({ m_specification.Width, m_specification.Height });

		m_window = std::make_unique<sf::RenderWindow>(videoMode, m_specification.Title);

		m_window->setVerticalSyncEnabled(m_specification.VSync);
	}

	void Window::Destroy()
	{
		if (m_window && m_window->isOpen())
			m_window->close();
		m_window.reset();
	}

	void Window::Update()
	{
		if (m_window)
			m_window->display();
	}

	void Window::ProcessEvents()
	{
		while (const std::optional event = m_window->pollEvent())
		{
			if (event->is<sf::Event::Closed>())
				m_window->close();
		}
	}

	sf::Vector2f Window::GetFrameBufferSize() const
	{
		if (m_window) {
			sf::Vector2f size = static_cast<sf::Vector2f>(m_window->getSize());
			return size;
		}
		return sf::Vector2f(0.0f, 0.0f);
	}

	bool Window::ShouldClose() const
	{
		return m_window ? !m_window->isOpen() : true;
	}
}