#pragma once

#include "Core.h"

namespace hazel {

	class __declspec(dllexport) Application {
	public:
		Application();
		virtual ~Application();

		void run();
	};

	Application* createApplication();
}

