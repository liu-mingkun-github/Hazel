#pragma once

#include "Core.h"
#include "Events/Event.h"

namespace Hazel {

	class __declspec(dllexport) Application {

	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}

