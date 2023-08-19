#pragma once

/*
	Differet kinds of events, if it is an event, if needs to inherit from the
	Event class
*/

#include "Event.h"

namespace Hazel {

	class HAZEL_API WindowResizeEvent : public Event {
		
	public:
		WindowResizeEvent(unsigned int width, unsigned int height)
			: m_width(width), m_height(height) {}

		inline unsigned int getWidth() const {
			return m_width;
		}

		inline unsigned int getHeight() const {
			return m_height;
		}

		std::string toString() const override {
			std::stringstream ss;
			ss << "WindowResizeEvent: " << m_width << ", " << m_height;
			return ss.str();
		}

		EVENT_CLASS_TYPE(WindowResize)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)

	private:
		unsigned int m_width, m_height;
	};

	class HAZEL_API WindowCloseEvent : public Event {

	public:
		WindowCloseEvent() {

		}

		EVENT_CLASS_TYPE(WindowClose)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppTickEvent : public Event {

	public:
		AppTickEvent() {

		}

		EVENT_CLASS_TYPE(AppTick)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};

	class HAZEL_API AppRenderEvent : public Event {

	public:
		AppRenderEvent() {

		}

		EVENT_CLASS_TYPE(AppRender)
		EVENT_CLASS_CATEGORY(EventCategoryApplication)
	};
}