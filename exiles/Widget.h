#pragma once

#include <functional>
#include <memory>
#include <string>
#include <vector>

#include <SFML/Graphics.hpp>

#include "Math.h"

class GUI;
class Layout;

class Widget
{
public:
	enum Action
	{
		Hover,
		Unhover,
		Press,
		Release,
		Focus,
		Unfocus,
		Enable,
		Disable,
		Show,
		Hide,

		ActionsNum
	};
	
	virtual ~Widget();

	void SetParent(Widget* widget);
	Widget* GetParent() const;

	void Bind(int action, std::function<void(Widget*)> function);
	void Trigger(int action);
	void Unbind(int action);

	void SetLayout(Layout* layout);
	Layout* GetLayout() const;

	void SetMinimumSize(float width, float height);
	void SetMinimumSize(const vec2& size);
	vec2 GetMinimumSize() const;

	void SetMaximumSize(float width, float height);
	void SetMaximumSize(const vec2& size);
	vec2 GetMaximumSize() const;

	void SetFixedWidth(float width);
	void SetFixedHeight(float height);
	void SetFixedSize(float width, float height);
	void SetFixedSize(const vec2& size);

	void SetSize(float width, float height);
	void SetSize(const vec2& size);
	vec2 GetSize() const;

	void SetPosition(float x, float y);
	void SetPosition(const vec2& position);
	vec2 GetPosition() const;

	sf::RectangleShape GetGeometry() const;
	sf::FloatRect GetRect() const;

	void SetOrigin(const vec2& origin);
	vec2 GetOrigin() const;

	void SetBackgroundColor(const sf::Color& color);
	sf::Color GetBackgroundColor() const;

	void SetEnabled(bool enabled);
	bool IsEnabled() const { return m_isEnabled; }

	void SetVisible(bool visible);
	bool IsVisible() const { return m_isVisible; }

	bool IsFocused() const { return m_isFocused; }
	bool IsHovered() const { return m_isHovered; }
	bool IsPressed() const { return m_isPressed; }

	unsigned int GetId() const { return m_id; }

	GUI* GetGUI() const { return m_gui; }
protected:
	friend class GUI;

	Widget();

	virtual void Update();
	virtual void Draw();

	Widget* m_parent;

	Layout* m_layout;

	sf::RectangleShape m_geometry;

	vec2 m_minimumSize;
	vec2 m_maximumSize;

	bool m_isEnabled;
	bool m_isVisible;

	bool m_isFocused;
	bool m_isHovered;
	bool m_isPressed;

	std::vector<std::function<void(Widget*)>> m_actions;

	static unsigned int CURRENT_ID;
	unsigned int m_id;

	GUI* m_gui;
};

typedef std::shared_ptr<Widget> widget_ptr;