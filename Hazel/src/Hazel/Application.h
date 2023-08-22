#pragma once

// Include Core.h for a bunch of macros
#include "Core.h"
#include "Window.h"

#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvent.h"

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
		// Whenever an Event wants to run, it is called through this method
		void onEvent(Event& e);

		void pushLayer(Layer* layer);
		// What this is for?
		void pushOverlay(Layer* overlay);

	private:
		// Why there are onEvent() and onWindowClose() Events? What's the difference?
		bool onWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_window;
		bool m_running = true;
		LayerStack m_layerStack;
	};

	// To be defined in CLIENT
	Application* createApplication();
}

