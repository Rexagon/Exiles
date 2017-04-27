#include "GUI.h"

#include <stack>

#include "Input.h"

#include "Shader.h"
#include "Core.h"

GUI::GUI()
{
	m_rootWidget = std::shared_ptr<Widget>(new Widget);
	m_rootWidget->m_gui = this;
	m_rootWidget->SetPosition(0.0f, 0.0f);
	sf::Vector2u size = Core::GetWindow()->getSize();
	m_rootWidget->SetSize(static_cast<float>(size.x), static_cast<float>(size.y));

	Layout* layout = new Layout(m_rootWidget);
}

void GUI::Update()
{
	vec2 mousePosition = Input::GetMousePosition();

	Widget* hoveredItem = nullptr;
	int hoveredItemIndex = -1;

	std::stack<Widget*> widgets;
	widgets.push(m_rootWidget.get());

	while (!widgets.empty()) {
		Widget* widget = widgets.top();
		widgets.pop();

		if (widget->m_layout) {
			std::vector<widget_ptr>& children = widget->m_layout->m_orderedWidgets;

			// проверка наведения
			int itemIndex = -1;
			for (unsigned int i = 0; i < children.size(); ++i) {
				if (i == 0) {
					widget->m_layout->Update();
				}
				if (children[i]->GetRect().contains(mousePosition.x, mousePosition.y)) {
					itemIndex = i;
					hoveredItem = children[i].get();
				}
			}

			if (itemIndex > -1) {
				hoveredItemIndex = itemIndex;
			}

			// обновление
			for (auto& child : children) {
				child->Update();
				widgets.push(child.get());
			}
		}
	}

	// при изменеии наведённого элемента
	if (hoveredItem != m_currentHoveredItem) {
		if (m_currentHoveredItem != nullptr) {
			m_currentHoveredItem->m_isHovered = false;
			m_currentHoveredItem->Trigger(Widget::Action::Unhover);
			m_currentHoveredItem = nullptr;
		}

		if (hoveredItem) {
			m_currentHoveredItem = hoveredItem;
			m_currentHoveredItem->m_isHovered = true;
			m_currentHoveredItem->Trigger(Widget::Action::Hover);
		}
	}

	// обработка нажатия
	if (m_currentHoveredItem != nullptr && Input::GetMouseDown(Mouse::Left)) {
		// двигаем нажатый элемент наверх по Z
		if (hoveredItemIndex > -1) {
			auto& orderedWidgets = m_currentHoveredItem->GetParent()->m_layout->m_orderedWidgets;
			std::rotate(orderedWidgets.begin() + hoveredItemIndex, orderedWidgets.begin() + hoveredItemIndex + 1,
						orderedWidgets.end());
		}

		m_currentHoveredItem->m_isPressed = true;
		m_currentHoveredItem->Trigger(Widget::Action::Press);
		m_currentPressedItem = m_currentHoveredItem;
	}

	if (m_currentPressedItem != nullptr && Input::GetMouseUp(Mouse::Left)) {
		m_currentPressedItem->m_isPressed = false;
		m_currentPressedItem->Trigger(Widget::Action::Release);
		m_currentPressedItem = nullptr;
	}
}

void GUI::Draw()
{
	std::stack<Widget*> widgets;
	widgets.push(m_rootWidget.get());

	while (!widgets.empty()) {
		Widget* widget = widgets.top();
		widgets.pop();

		if (widget->m_layout) {
			std::vector<widget_ptr>& children = widget->m_layout->m_orderedWidgets;

			for (auto& child : children) {
				child->Draw();
				widgets.push(child.get());
			}
		}
	}
}