#include <Hazel.h>

class ExampleLayer : public Hazel::Layer {
public:
	ExampleLayer()
		: Layer("Example") {}

	void onUpdate() override {
		HZ_INFO("ExampleLayer::update");
	}

	void onEvent(Hazel::Event& event) override {
		HZ_TRACE("{0}", event);
	}
};

// Because Sandbox is basically an instance of Hazel,
// so Sandbox project will inherit and override the Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() {
		pushLayer(new ExampleLayer());
	}

	~Sandbox() {

	}
};

// Define the function in the application.h
Hazel::Application* Hazel::createApplication() {
	return new Sandbox();
}