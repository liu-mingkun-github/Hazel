#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy might be to buffer events in an event
	// bus and process them during the "event" of the update stage.

	// Enumerate different Event Types
	enum class EventType {
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
		AppTick, AppUpdate, AppRender,
		KeyPressed, KeyReleased, KeyTyped,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	// BIT is a macros in Core.h
	// An event can be of multiple categories
	enum EventCategory {
		None = 0,
		EventCategoryApplication	= BIT(0),
		EventCategoryInput			= BIT(1),
		EventCategoryKeyboard		= BIT(2),
		EventCategoryMouse			= BIT(3),
		EventCategoryMouseButton	= BIT(4)
	};

// ## is used to concatenate two tokens into one, it cannot be used in the head or tail
// Like here is to concat EventType and type.
// Remember in macros, all the things are strings.
// The macros here basically just override the methods in the Event class
// Need to have both static and non-static methods for different situations:
// Class::getStaticType() or instance.getType()
#define EVENT_CLASS_TYPE(type) static EventType getStaticType() { return EventType::##type; }\
																virtual EventType getEventType() const override { return getStaticType(); }\
																virtual const char* getName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int getCategoryFlags() const override { return category; }

	class HAZEL_API Event {

	private:
		// A friend class can access the private and protected members of the class
		 //in which it is declared as a friend.
		// So now Event can access EventDispatcher
		//friend class EventDispatcher;

	public:
		bool handled = false;

		// All methods here are pure virtual methods
		virtual EventType getEventType() const = 0;

		virtual const char* getName() const = 0;

		virtual int getCategoryFlags() const = 0;

		virtual std::string toString() const { 
			return getName(); 
		}

		inline bool isInCategory(EventCategory category) {
			return getCategoryFlags() & category;
		}

	/*protected:
		bool m_handled = false;*/
	};

	class EventDispatcher {

	private:
		template<typename T>
		// A function that returns a bool and use T& as the parameter
		using eventFn = std::function<bool(T&)>;

	public:
		EventDispatcher(Event& event)
			: m_event(event) {}

		// F will be deduced by the compiler
		template<typename T>
		bool dispatch(eventFn<T> func) {
			if (m_event.getEventType() == T::getStaticType()) {
				// Call the std::function<bool(T&)>
				// Here we convert Event pointer to T type pointer and get its reference
				m_event.handled = func(*(T*)&m_event);
				return true;
			}
			return false;
		}

	private:
		Event& m_event;
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e) {
		return os << e.toString();
	}
}