#include "Widget.h"

Widget::Widget(Widget * parent) :
	m_parent(parent), m_isEnabled(true), m_isVisible(true)
{
}

Widget::~Widget()
{
}

void Widget::SetParent(Widget * parent)
{
}
