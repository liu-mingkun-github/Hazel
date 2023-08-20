#include "hzpch.h"
#include "Application.h"

#include "Hazel/Log.h"

#include <GLFW/glfw3.h>

namespace Hazel {

	// std::bind() is used to create partial functions, that you can use the partial arguments
	// of the original function and use it to create a new function.
	// Now, this defined function defines that we need to pass a function in the scope of Application
	// and pass two arguements: this class and an argument which is in the second position of the original function.
#define BIND_EVENT_FN(x) std::bind(&Application::x, this, std::placeholders::_1)

	// Application class's constructor
	Application::Application() {
		// create a unique pointer that points to a window
		m_window = std::unique_ptr<Window>(Window::create());
		// To set the event that the winndow calls, pass in a function
		m_window->setEventCallback(BIND_EVENT_FN(onEvent));
	}

	Application::~Application() {

	}

	void Application::onEvent(Event& e) {
		EventDispatcher dispatcher(e);
		// Here dispatch<WindowCloseEvent> means to dispatch a WindowCloseEvent type event
		// This is a function template
		dispatcher.dispatch<WindowCloseEvent>(BIND_EVENT_FN(onWindowClose));

		HZ_CORE_TRACE("{0}", e);
	}

	void Application::run() {
		/*WindowResizeEvent e(1280, 720);
		if (e.isInCategory(EventCategoryApplication)) {
			while (m_running) {
				HZ_TRACE(e);
				glClearColor(1, 0, 1, 1);
				m_window->onUpdate();
			}
		}
		if (e.isInCategory(EventCategoryInput)) {
			HZ_TRACE(e);
		}

		while (true);*/

		while (m_running) {
			glClearColor(1, 0, 1, 1);
			glClear(GL_COLOR_BUFFER_BIT);
			m_window->onUpdate();
		}
	}

	// To be defined in CLIENT
	// .cpp file can also define
	// .cpp file can have declaration, definition, and callback
	Application* createApplication();

	bool Application::onWindowClose(WindowCloseEvent& e) {
		m_running = false;
		return true;
	}
}