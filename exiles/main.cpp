#include "Core.h"
#include "Window.h"

#include "MainMenu.h"

int main()
{
	try {
		Log::Create();

		Window::Create("Exiles", 800, 600);

		Core::Push<MainMenu>();
		Core::Run();

		Window::Close();
	}
	catch (const std::exception& e) {
		Log::Write("[ERROR]", e.what());
	}

	return 0;
}