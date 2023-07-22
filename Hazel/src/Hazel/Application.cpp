#include "Application.h"

namespace hazel {

	Application::Application() {

	}

	Application::~Application() {

	}

	void Application::run() {
		while (true);
	}

	// To be defined in CLIENT
	Application* createApplication();
}