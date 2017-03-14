#include "MainMenu.h"

#include "Core.h"
#include "Window.h"
#include "Input.h"

#include "Texture.h"
#include "Shader.h"

void MainMenu::OnInit()
{
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
	Window::Clear();
}
