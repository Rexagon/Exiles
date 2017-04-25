#include "Core.h"
#include "Window.h"

#include "MainMenu.h"

int main()
{
	try {
		Core::Init("Exiles");
		Core::Push<MainMenu>();
		Core::Run();
	}
	catch (const std::exception& e) {
		Log::Write("[ERROR]", e.what());
	}

	return 0;
}