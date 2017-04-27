#include "MainMenu.h"

#include "Core.h"
#include "Input.h"

void MainMenu::OnInit()
{
	auto window = m_gui.CreateItem<Widget>();
	window->SetPosition(100, 100);
	window->SetSize(600.0f, 300.0f);
	window->SetBackgroundColor(sf::Color(40, 40, 40));

	HorizontalLayout* layout = new HorizontalLayout(window);
	layout->SetSpacing(10.0f);

	for (int i = 0; i < 6; ++i) {
		auto widget = m_gui.CreateItem<Widget>();
		widget->SetBackgroundColor(sf::Color(120, 160, 150));

		layout->AddWidget(widget);
	}

	m_gui.GetRootWidget()->GetLayout()->AddWidget(window);
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
}
