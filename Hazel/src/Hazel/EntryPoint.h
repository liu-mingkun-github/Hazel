#pragma once

// The entry point basically create an entry for the client application (like Sandbox)
// to call and use the Hazel project.

#ifdef HZ_PLATFORM_WINDOWS

// The extern keyword tells the compiler the variable or function
// has already been defined or will be defined at the linking stage.

// Basically, it tells the compiler I am sure I have declared and defined this variable or function
// somewhere else, you don't need to worry about it.

// To use extern, you don't need to provide definition in this file
// but expect it to be defined in somewhere else.

// For example, now Sandbox has provided a definition for this function.

// This extern can let the file that calls this function provides it own definition.
extern Hazel::Application* Hazel::createApplication();

int main(int argc, char** argv) {

	Hazel::Log::init();
	HZ_CORE_WARN("Initialized Log!");
	int a = 5;
	HZ_INFO("Hello! Var={0}", a);

	
	auto app = Hazel::createApplication();
	app->run();
	// When you delete a pointer, you are actually delete the address it points to
	delete app;
	app = nullptr;
}

#endif