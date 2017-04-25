#include "Input.h"

#include <SDL2\SDL.h>

#include "Core.h"
#include "Window.h"

const int Input::NUM_KEYS = 512;
const int Input::NUM_MOUSEBUTTONS = 256;

ivec2 Input::m_mousePosition = ivec2(0, 0);

std::vector<bool> Input::m_currentKeysState = std::vector<bool>(NUM_KEYS, false);
std::vector<bool> Input::m_lastKeysState = std::vector<bool>(NUM_KEYS, false);

std::vector<bool> Input::m_currentMouseButtonsState = std::vector<bool>(NUM_MOUSEBUTTONS, false);
std::vector<bool> Input::m_lastMouseButtonsState = std::vector<bool>(NUM_MOUSEBUTTONS, false);

void Input::Update()
{
	m_lastKeysState = m_currentKeysState;
	m_lastMouseButtonsState = m_currentMouseButtonsState;
}

bool Input::GetKey(Key keyCode)
{
	return m_currentKeysState[keyCode];
}

bool Input::GetKeyDown(Key keyCode)
{
	return m_currentKeysState[keyCode] &&
			!m_lastKeysState[keyCode];
}

bool Input::GetKeyUp(Key keyCode)
{
	return !m_currentKeysState[keyCode] &&
			m_lastKeysState[keyCode];
}

bool Input::GetMouse(Mouse button)
{
	return m_currentMouseButtonsState[button];
}

bool Input::GetMouseDown(Mouse button)
{
	return m_currentMouseButtonsState[button] &&
			!m_lastMouseButtonsState[button];
}

bool Input::GetMouseUp(Mouse button)
{
	return !m_currentMouseButtonsState[button] &&
			m_lastMouseButtonsState[button];
}

ivec2 Input::GetMousePosition()
{
	return m_mousePosition;
}