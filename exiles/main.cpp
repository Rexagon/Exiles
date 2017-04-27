#include "Core.h"

#include "MainMenu.h"

int main()
{
	try {
		Log::Create();

		Core::Init("Exiles");
		Core::Push<MainMenu>();
		Core::Run();
	}
	catch (const std::runtime_error& e) {
		Log::Write("[ERROR]", e.what());
	}

	return 0;
}