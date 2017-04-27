#pragma once

#include <vector>

#include <SFML/Graphics.hpp>

#include "Math.h"

using Key = sf::Keyboard::Key;
using Mouse = sf::Mouse::Button;

class Input
{
public:
	// Обновляет состояния клавиш
	static void Update();

	// Нажата ли клавиша в текущий момент
	static bool GetKey(sf::Keyboard::Key keyCode);

	// Произошло ли нажатие клавиши в этом кадре
	static bool GetKeyDown(sf::Keyboard::Key keyCode);

	// Отпустили ли клавишу в этом кадре
	static bool GetKeyUp(sf::Keyboard::Key keyCode);


	// Нажата ли кнопка мыши в текущий момент
	static bool GetMouse(sf::Mouse::Button button);

	// Произошло ли нажатие кнопки мыши в этом кадре
	static bool GetMouseDown(sf::Mouse::Button button);

	// Отпустили ли кнопку мыши в этом кадре
	static bool GetMouseUp(sf::Mouse::Button button);

	// Позиция курсора относительно левого верхнего угла окна
	static vec2 GetMousePosition();
private:
	friend class Core;

	const static int NUM_KEYS;
	const static int NUM_MOUSEBUTTONS;

	static vec2 m_mousePosition;

	static std::vector<bool> m_currentKeysState;
	static std::vector<bool> m_lastKeysState;

	static std::vector<bool> m_currentMouseButtonsState;
	static std::vector<bool> m_lastMouseButtonsState;
};