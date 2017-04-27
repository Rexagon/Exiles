#include "Input.h"

#include "Core.h"

const int Input::NUM_KEYS = sf::Keyboard::KeyCount;
const int Input::NUM_MOUSEBUTTONS = sf::Mouse::ButtonCount;

vec2 Input::m_mousePosition = vec2(0, 0);

std::vector<bool> Input::m_currentKeysState = std::vector<bool>(NUM_KEYS, false);
std::vector<bool> Input::m_lastKeysState = std::vector<bool>(NUM_KEYS, false);

std::vector<bool> Input::m_currentMouseButtonsState = std::vector<bool>(NUM_MOUSEBUTTONS, false);
std::vector<bool> Input::m_lastMouseButtonsState = std::vector<bool>(NUM_MOUSEBUTTONS, false);

void Input::Update()
{
	m_lastKeysState = m_currentKeysState;
	m_lastMouseButtonsState = m_currentMouseButtonsState;
}

bool Input::GetKey(sf::Keyboard::Key keyCode)
{
	return m_currentKeysState[keyCode];
}

bool Input::GetKeyDown(sf::Keyboard::Key keyCode)
{
	return m_currentKeysState[keyCode] &&
			!m_lastKeysState[keyCode];
}

bool Input::GetKeyUp(sf::Keyboard::Key keyCode)
{
	return !m_currentKeysState[keyCode] &&
			m_lastKeysState[keyCode];
}

bool Input::GetMouse(sf::Mouse::Button button)
{
	return m_currentMouseButtonsState[button];
}

bool Input::GetMouseDown(sf::Mouse::Button button)
{
	return m_currentMouseButtonsState[button] &&
			!m_lastMouseButtonsState[button];
}

bool Input::GetMouseUp(sf::Mouse::Button button)
{
	return !m_currentMouseButtonsState[button] &&
			m_lastMouseButtonsState[button];
}

vec2 Input::GetMousePosition()
{
	return m_mousePosition;
}