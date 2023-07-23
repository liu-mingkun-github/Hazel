#include "Application.h"

namespace Hazel {

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