#include <Hazel.h>

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void onUpdate() override {
		//HZ_INFO("ExampleLayer::update");
		if (Hazel::Input::isKeyPressed(HZ_KEY_TAB))
		{
			HZ_TRACE("Tab key is pressed (poll)!");
		}
	}

	void onEvent(Hazel::Event& event) override {
		//HZ_TRACE("{0}", event);
		if (event.getEventType() == Hazel::EventType::KeyPressed)
		{
			Hazel::KeyPressedEvent& e = (Hazel::KeyPressedEvent&)event;
			if (e.getKeyCode() == HZ_KEY_TAB)
			{
				HZ_TRACE("Tab key is pressed (event)!");
			}
			HZ_TRACE("{0}", (char)e.getKeyCode());
		}
	}
};

// Because Sandbox is basically an instance of Hazel,
// so Sandbox project will inherit and override the Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		pushLayer(new ExampleLayer());
		pushOverlay(new Hazel::ImGuiLayer());
	}

	~Sandbox() {

	}
};

// Define the function in the application.h
Hazel::Application* Hazel::createApplication() {
	return new Sandbox();
}