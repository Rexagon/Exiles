#include "Widget.h"

#include "Core.h"
#include "GUI.h"

unsigned int Widget::CURRENT_ID = 0;

Widget::Widget() :
	m_parent(nullptr), m_layout(nullptr), m_isEnabled(true), m_isVisible(true), 
	m_id(CURRENT_ID++), m_gui(nullptr),	m_minimumSize(0.0f, 0.0f), m_maximumSize(16384.0f)
{
	m_actions.resize(ActionsNum, [](Widget*) {});
}

Widget::~Widget()
{
	delete m_layout;
	Log::Write("Widget", m_id, "deleted");
}

void Widget::SetParent(Widget* widget)
{
	m_parent = widget;
}

Widget* Widget::GetParent() const
{
	return m_parent;
}

void Widget::Update()
{
}

void Widget::Draw()
{
	Core::GetWindow()->draw(m_geometry);
}

void Widget::Bind(int action, std::function<void(Widget*)> function)
{
	if (action > -1 && action < ActionsNum) {
		m_actions[action] = function;
	}
}

void Widget::Trigger(int action)
{
	if (action > -1 && action < ActionsNum) {
		m_actions[action](this);
	}
}

void Widget::Unbind(int action)
{
	if (action > -1 && action < ActionsNum) {
		m_actions[action] = [](Widget*) {};
	}
}

void Widget::SetLayout(Layout * layout)
{
	delete m_layout;
	m_layout = layout;
	m_layout->m_parent = this;
}

Layout * Widget::GetLayout() const
{
	return m_layout;
}

void Widget::SetMinimumSize(float width, float height)
{
	SetMinimumSize(vec2(width, height));
}

void Widget::SetMinimumSize(const vec2 & size)
{
	m_minimumSize = size;
}

vec2 Widget::GetMinimumSize() const
{
	return m_minimumSize;
}

void Widget::SetMaximumSize(float width, float height)
{
	SetMaximumSize(vec2(width, height));
}

void Widget::SetMaximumSize(const vec2 & size)
{
	m_maximumSize = size;
}

vec2 Widget::GetMaximumSize() const
{
	return m_maximumSize;
}

void Widget::SetFixedWidth(float width)
{
	m_minimumSize.x = width;
	m_maximumSize.x = width;
	SetSize(width, m_geometry.getSize().y);
}

void Widget::SetFixedHeight(float height)
{
	m_minimumSize.y = height;
	m_maximumSize.y = height;
	SetSize(m_geometry.getSize().x, height);
}

void Widget::SetFixedSize(float width, float height)
{
	SetMinimumSize(width, height);
	SetMaximumSize(width, height);
	SetSize(width, height);
}

void Widget::SetFixedSize(const vec2 & size)
{
	SetFixedSize(size.x, size.y);
}

void Widget::SetSize(float width, float height)
{
	if (width < m_minimumSize.x) {
		width = m_minimumSize.x;
	}

	if (width > m_maximumSize.x) {
		width = m_maximumSize.x;
	}

	if (height < m_minimumSize.y) {
		height = m_minimumSize.y;
	}

	if (height > m_maximumSize.y) {
		height = m_maximumSize.y;
	}

	m_geometry.setSize(sf::Vector2f(width, height));
}

void Widget::SetSize(const vec2 & size)
{
	SetSize(size.x, size.y);
}

vec2 Widget::GetSize() const
{
	sf::Vector2f size = m_geometry.getSize();
	return vec2(size.x, size.y);
}

void Widget::SetPosition(float x, float y)
{
	m_geometry.setPosition(x, y);
}

void Widget::SetPosition(const vec2 & position)
{
	SetPosition(position.x, position.y);
}

vec2 Widget::GetPosition() const
{
	sf::Vector2f position = m_geometry.getPosition();
	return vec2(position.x, position.y);
}

sf::RectangleShape Widget::GetGeometry() const
{
	return m_geometry;
}

sf::FloatRect Widget::GetRect() const
{
	return m_geometry.getGlobalBounds();
}

void Widget::SetOrigin(const vec2 & origin)
{
	m_geometry.setOrigin(origin.x, origin.y);
}

vec2 Widget::GetOrigin() const
{
	return vec2(m_geometry.getOrigin().x, m_geometry.getOrigin().y);
}

void Widget::SetBackgroundColor(const sf::Color & color)
{
	m_geometry.setFillColor(color);
}

sf::Color Widget::GetBackgroundColor() const
{
	return m_geometry.getFillColor();
}

void Widget::SetEnabled(bool enabled)
{
	bool wasEnabled = m_isEnabled;
	m_isEnabled = enabled;
	if (wasEnabled != m_isEnabled) {
		if (m_isEnabled) {
			m_actions[Enable](this);
		}
		else {
			m_actions[Disable](this);
		}
	}
}

void Widget::SetVisible(bool visible)
{
	bool wasVisible = m_isVisible;
	m_isVisible = visible;
	if (wasVisible != m_isVisible) {
		if (m_isVisible) {
			m_actions[Show](this);
		}
		else {
			m_actions[Hide](this);
		}
	}
}
