#include "hzpch.h"
#include "Application.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Log.h"

namespace Hazel {

	Application::Application() {

	}

	Application::~Application() {

	}
	
	void Application::run() {
		WindowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategoryApplication)) {
			HZ_TRACE(e);
		}
		if (e.isInCategory(EventCategoryInput)) {
			HZ_TRACE(e);
		}

		while (true);
	}

	// To be defined in CLIENT
	Application* createApplication();
}