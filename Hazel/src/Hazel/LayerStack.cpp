#include "hzpch.h"
#include "LayerStack.h"

namespace Hazel {

	LayerStack::LayerStack() {
		m_layerInsert = m_layers.begin();
	}

	LayerStack::~LayerStack() {
		for (Layer* layer : m_layers) {
			delete layer;
		}
	}

	void LayerStack::pushLayer(Layer* layer) {
		// emplace() insert a new element at position
		m_layerInsert = m_layers.emplace(m_layerInsert, layer);
	}

	void LayerStack::pushOverlay(Layer* overlay) {
		// Whereas emplace_back() push to the end of the vector.
		m_layers.emplace_back(overlay);
	}

	void LayerStack::popLayer(Layer* layer) {
		// Traverse and find the layer
		auto it = std::find(m_layers.begin(), m_layers.end(), layer);
		if (it != m_layers.end()) {
			m_layers.erase(it);
			m_layerInsert--;
		}
	}

	void LayerStack::popOverlay(Layer* overlay) {
		// Here overlay is treated the same as the normal layer
		// I think it should be more specific to the overlay.
		auto it = std::find(m_layers.begin(), m_layers.end(), overlay);
		if (it != m_layers.end()) {
			m_layers.erase(it);
		}
	}
}