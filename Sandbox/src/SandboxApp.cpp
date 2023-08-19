#include <Hazel.h>

// Because Sandbox is basically an instance of Hazel,
// so Sandbox project will inherit and override the Hazel
class Sandbox : public Hazel::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

// Define the function in the application.h
Hazel::Application* Hazel::createApplication() {
	return new Sandbox();
}