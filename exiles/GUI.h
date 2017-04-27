#pragma once

#include <memory>
#include <vector>
#include <string>
#include <map>

#include "Widget.h"

#include "VerticalLayout.h"
#include "HorizontalLayout.h"

#include "Label.h"

class GUI
{
public:
	GUI();

	// Обновляет состояния элементов, нажатия, наведения
	void Update();

	// Рисует элементы в заданном порядке
	void Draw();

	widget_ptr GetRootWidget() const { return m_rootWidget; }

	template<class T, class... Args>
	std::shared_ptr<T> CreateItem(Args&&... args)
	{
		static_assert(std::is_base_of<Widget, T>::value, "GUI::Create template argument must be the child class of \"Widget\" class");
		std::shared_ptr<T> widget = std::shared_ptr<T>(new T(std::forward(args)...));
		widget->m_gui = this;
		return std::move(widget);
	}
private:
	widget_ptr m_rootWidget;

	Widget* m_currentHoveredItem;
	Widget* m_currentPressedItem;
	Widget* m_currentFocusedItem;
};