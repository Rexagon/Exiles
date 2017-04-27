#include "Layout.h"

#include "GUI.h"

Layout::Layout() :
	m_parent(nullptr)
{
}

Layout::Layout(widget_ptr parent) :
	m_parent(parent.get())
{
	parent->SetLayout(this);
}

Layout::~Layout()
{
}

void Layout::AddWidget(widget_ptr widget)
{
	widget->SetParent(m_parent);
	m_orderedWidgets.push_back(widget);
	m_items.push_back(Item(widget.get()));
	Update();
}

void Layout::RemoveWidget(widget_ptr widget)
{
	for (auto it = m_items.begin(); it != m_items.end(); ++it) {
		if ((*it).widget == widget.get()) {
			m_items.erase(it);
			break;
		}
	}
	for (auto it = m_orderedWidgets.begin(); it != m_orderedWidgets.end(); ++it) {
		if ((*it) == widget) {
			m_orderedWidgets.erase(it);
			break;
		}
	}
	Update();
}

int Layout::IndexOf(widget_ptr widget) const
{
	for (unsigned int i = 0; i < m_items.size(); ++i) {
		if (m_items[i].widget == widget.get()) {
			return i;
		}
	}
	return -1;
}

Widget * Layout::TakeAt(int index) const
{
	if (index > -1 && index < m_items.size()) {
		return m_items[index].widget;
	}
	return nullptr;
}

void Layout::SetAlignment(int alignment)
{
	if (!(alignment & AlignLeft ||
		alignment & AlignRight ||
		alignment & AlignHCenter)) {
		alignment |= AlignHCenter;
	}

	if (!(alignment & AlignTop ||
		alignment & AlignBottom ||
		alignment & AlignVCenter)) {
		alignment |= AlignVCenter;
	}

	for (unsigned int i = 0; i < m_items.size(); ++i) {
		m_items[i].alignment = alignment;
	}
	Update();
}

void Layout::SetAlignment(widget_ptr widget, int alignment)
{
	if (!(alignment & AlignLeft ||
		alignment & AlignRight ||
		alignment & AlignHCenter)) {
		alignment |= AlignHCenter;
	}

	if (!(alignment & AlignTop ||
		alignment & AlignBottom ||
		alignment & AlignVCenter)) {
		alignment |= AlignVCenter;
	}

	for (unsigned int i = 0; i < m_items.size(); ++i) {
		if (widget == nullptr || m_items[i].widget == widget.get()) {
			m_items[i].alignment = alignment;
		}
	}
	Update();
}

void Layout::Update()
{
}
