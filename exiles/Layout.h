#pragma once

#include <vector>

#include "Widget.h"

class Layout
{
public:
	enum Alignment
	{
		AlignLeft		= 1 << 0,
		AlignRight		= 1 << 1,
		AlignHCenter	= 1 << 2,

		AlignTop		= 1 << 3,
		AlignBottom		= 1 << 4,
		AlignVCenter	= 1 << 5,

		AlignCenter		= AlignHCenter | AlignVCenter
	};

	struct Item
	{
		Item(Widget* widget, int alignment = AlignCenter) :
			widget(widget), alignment(alignment) {}

		Widget* widget;
		int alignment;
	};

	Layout();
	Layout(widget_ptr parent);
	~Layout();

	virtual void AddWidget(widget_ptr widget);
	virtual void RemoveWidget(widget_ptr widget);

	virtual int IndexOf(widget_ptr widget) const;
	virtual Widget* TakeAt(int index) const;

	void SetAlignment(int alignment);
	void SetAlignment(widget_ptr widget, int alignment);

	void SetSpacing(float spacing) { m_spacing = spacing; }
	float GetSpacing() const { return m_spacing; }
protected:
	friend class GUI;
	friend class Widget;

	virtual void Update();

	Widget* m_parent;

	float m_spacing;

	std::vector<Item> m_items;
	std::vector<widget_ptr> m_orderedWidgets;
};