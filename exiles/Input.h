#pragma once

#include <vector>

#include "Math.h"

class Input
{
public:
	enum Mouse
	{
		ButtonLeft = 1,
		ButtonMiddle = 2,
		ButtonRight = 3,
		WheelUp = 4,
		WheelDown = 5
	};

	enum Key
	{
		Unknown = 0,

		A = 4,
		B = 5,
		C = 6,
		D = 7,
		E = 8,
		F = 9,
		G = 10,
		H = 11,
		I = 12,
		J = 13,
		K = 14,
		L = 15,
		M = 16,
		N = 17,
		O = 18,
		P = 19,
		Q = 20,
		R = 21,
		S = 22,
		T = 23,
		U = 24,
		V = 25,
		W = 26,
		X = 27,
		Y = 28,
		Z = 29,

		// not numpad, just numbers
		Num1 = 30,
		Num2 = 31,
		Num3 = 32,
		Num4 = 33,
		Num5 = 34,
		Num6 = 35,
		Num7 = 36,
		Num8 = 37,
		Num9 = 38,
		Num0 = 39,

		Enter = 40,
		Escape = 41,
		Backspace = 42,
		Tab = 43,
		Space = 44,

		Minus = 45,
		Equals = 46,
		LeftBracket = 47,
		RightBracket = 48,
		BackSlash = 49,
		Nonushash = 50,
		Semicolon = 51,
		Apostrophe = 52,
		Grave = 53,
		Comma = 54,
		Period = 55,
		Slash = 56,

		CapsLock = 57,

		F1 = 58,
		F2 = 59,
		F3 = 60,
		F4 = 61,
		F5 = 62,
		F6 = 63,
		F7 = 64,
		F8 = 65,
		F9 = 66,
		F10 = 67,
		F11 = 68,
		F12 = 69,

		PrintScreen = 70,
		ScrollLock = 71,
		Pause = 72,
		Insert = 73,
		Home = 74,
		PageUp = 75,
		Delete = 76,
		End = 77,
		PageDown = 78,
		Right = 79,
		Left = 80,
		Down = 81,
		Up = 82,

		NumpadLock = 83,
		NumpadDivide = 84,
		NumpadMultiply = 85,
		NumpadMinus = 86,
		NumpadPlus = 87,
		NumpadEnter = 88,
		Numpad1 = 89,
		Numpad2 = 90,
		Numpad3 = 91,
		Numpad4 = 92,
		Numpad5 = 93,
		Numpad6 = 94,
		Numpad7 = 95,
		Numpad8 = 96,
		Numpad9 = 97,
		Numpad0 = 98,
		NumpadPeriod = 99,

		LeftCtrl = 224,
		LeftShift = 225,
		LeftAlt = 226, /**< alt, option */
		LeftGUI = 227, /**< windows, command (apple), meta */
		RightCtrl = 228,
		RightShift = 229,
		RightAlt = 230, /**< alt gr, option */
		RightGUI = 231, /**< windows, command (apple), meta */
	};

	// Обновляет состояния клавиш
	static void Update();

	// Нажата ли клавиша в текущий момент
	static bool GetKey(Key keyCode);

	// Произошло ли нажатие клавиши в этом кадре
	static bool GetKeyDown(Key keyCode);

	// Отпустили ли клавишу в этом кадре
	static bool GetKeyUp(Key keyCode);


	// Нажата ли кнопка мыши в текущий момент
	static bool GetMouse(Mouse button);

	// Произошло ли нажатие кнопки мыши в этом кадре
	static bool GetMouseDown(Mouse button);

	// Отпустили ли кнопку мыши в этом кадре
	static bool GetMouseUp(Mouse button);

	// Позиция курсора относительно левого верхнего угла окна
	static ivec2 GetMousePosition();
private:
	friend class Core;

	const static int NUM_KEYS;
	const static int NUM_MOUSEBUTTONS;

	static ivec2 m_mousePosition;

	static std::vector<bool> m_currentKeysState;
	static std::vector<bool> m_lastKeysState;

	static std::vector<bool> m_currentMouseButtonsState;
	static std::vector<bool> m_lastMouseButtonsState;
};

using Key = Input::Key;
using Mouse = Input::Mouse;