#pragma once

// Include Core.h for a bunch of macros
#include "Core.h"
#include "Events/Event.h"
#include "Window.h"

namespace Hazel {
	// __declspec is a Microsoft specific extenstions 
	// that allows you to import or export a symbol from or to a DLL.
	// 
	// In this case, the Application class is marked with __declspec,
	// which means if this class is compiled into a DLL, it will be 
	// accessible for use by other applications that link against that DLL.
	// = Put this class into the DLL

	// The reason we need to export it to a dll is because 
	// Sandbox needs to use the dll.
	class HAZEL_API Application {

	public:
		// Constructor
		Application();
		// Destructor
		// virtual means it can be overriden in its derived classes.
		// Functions without virutal keyword cannot be overriden
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

