#pragma once

#include "Hazel/Layer.h"

namespace Hazel {

	class HAZEL_API ImGuiLayer : public Layer {
		
	public:
		ImGuiLayer();
		~ImGuiLayer();

		void onAttach();
		void onDetach();
		void onUpdate();
		void onEvent();

	private:
		float m_time = 0.0f;
	};
}

