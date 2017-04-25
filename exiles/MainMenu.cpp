#include "MainMenu.h"

#include "Core.h"
#include "Window.h"
#include "Input.h"

void MainMenu::OnInit()
{
	Core::GetWindow()->SetClearColor(vec4(0.2f, 0.2f, 0.2f, 1.0f));	
}

void MainMenu::OnUpdate(const float dt)
{

	if (Input::GetKey(Key::Escape)) {
		Core::PopState();
		return;
	}
}

void MainMenu::OnDraw(const float dt)
{
	Core::GetWindow()->Clear();
}
