#include <Hazel.h>

class Sandbox : public hazel::Application {
public:
	Sandbox() {

	}

	~Sandbox() {

	}
};

hazel::Application* hazel::createApplication() {
	return new Sandbox();
}