#pragma once

#include "Hazel/Core.h"
#include "Hazel/Events/Event.h"

namespace Hazel {

	class HAZEL_API Layer {
	public:
		Layer(const std::string& name = "Layer");
		
		virtual ~Layer();

		// Various basic layer functions
		virtual void onAttach() {}
		virtual void onDetach() {}
		virtual void onUpdate() {}
		virtual void onEvent(Event& event) {}

		inline const std::string& getName() const {
			return m_debugName;
		}

	protected:
		std::string m_debugName;
	};
}

