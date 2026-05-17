#pragma once
#include <SFML/Graphics.hpp>
#include <Core/Application.h>

namespace Renderer
{
	class Renderer
	{
	public:
		template<typename TDrawable>
			requires std::is_base_of_v<sf::Drawable, TDrawable>
		static void Draw(const TDrawable& drawable) {
			auto window = Application::Get().GetWindow()->GetHandle();
			if (window)
				window->draw(drawable);
		}

		static void Clear() {
			auto window = Core::Application::Get().GetWindow()->GetHandle();
			if (window)
				window->clear();
		}
	};
}