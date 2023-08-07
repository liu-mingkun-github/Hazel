#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Hazel {

	class __declspec(dllexport) Application {

	public:
		Application();
		virtual ~Application();

		void run();

		// This method is for responding the proper calling events
		void onEvent(Event& e);

	private:
		std::unique_ptr<Window> m_window;
		bool m_running = true;
	};

	// To be defined in CLIENT
	Application* createApplication();
}

