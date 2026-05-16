#include "Layer.h"
#include "Application.h"

void Layer::QueueTransition(std::unique_ptr<Layer> layer)
{
	// This code will change, stays for now
	auto& layerStack = Application::Get().m_layerStack;
	for(auto& layer : layerStack) {
		if (layer.get() == this) {
			layer = std::move(layer);
			return;
		}
	}
}
