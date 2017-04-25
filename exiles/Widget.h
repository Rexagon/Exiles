#pragma once

#include "Math.h"

class Widget
{
public:
	Widget(Widget* parent = nullptr);
	virtual ~Widget();

	virtual void Update() {}
	virtual void Draw() {}

	void SetParent(Widget* parent);
	Widget* GetParent() const { return m_parent; }

	void SetRect(const rect& rectangle) { m_rectangle = rectangle; }
	rect GetRect() const { return m_rectangle; }

	void SetEnabled(bool enabled) { m_isEnabled = enabled; }
	bool IsEnabled() const { return m_isEnabled; }

	void SetVisible(bool visible) { m_isVisible = visible; }
	bool IsVisible() const { return m_isVisible; }

	void SetFocus(bool focus) { m_isFocused = focus; }
	bool IsFocused() const { return m_isFocused; }
private:
	Widget* m_parent;

	rect m_rectangle;

	bool m_isEnabled;
	bool m_isVisible;
	bool m_isFocused;
};