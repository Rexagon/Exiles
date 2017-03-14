#include "Input.h"

#include <SDL2\SDL.h>

#include "Core.h"
#include "Window.h"

const static int NUM_KEYS = 512;
const static int NUM_MOUSEBUTTONS = 256;

static int mouseX = 0;
static int mouseY = 0;

static bool inputs[NUM_KEYS];
static bool downKeys[NUM_KEYS];
static bool upKeys[NUM_KEYS];

static bool mouseInput[NUM_MOUSEBUTTONS];
static bool downMouse[NUM_MOUSEBUTTONS];
static bool upMouse[NUM_MOUSEBUTTONS];

void Input::Update()
{
	for (int i = 0; i < NUM_MOUSEBUTTONS; i++) {
		downMouse[i] = false;
		upMouse[i] = false;
	}

	for (int i = 0; i < NUM_KEYS; i++) {
		downKeys[i] = false;
		upKeys[i] = false;
	}

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		int value = 0;

		switch (e.type) {
		case SDL_QUIT:
			Core::Stop();
			break;

		case SDL_WINDOWEVENT_FOCUS_GAINED:
			Window::m_isFocused = true;
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST: 
		case SDL_WINDOWEVENT_HIDDEN:
			Window::m_isFocused = false;
			break;
		case SDL_MOUSEMOTION:
			mouseX = e.motion.x;
			mouseY = e.motion.y;
			break;
		case SDL_KEYDOWN:
			value = e.key.keysym.scancode;
			inputs[value] = true;
			downKeys[value] = true;
			break;
		case SDL_KEYUP:
			value = e.key.keysym.scancode;
			inputs[value] = false;
			upKeys[value] = true;
			break;
		case SDL_MOUSEBUTTONDOWN:
			value = e.button.button;
			mouseInput[value] = true;
			downMouse[value] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			value = e.button.button;
			mouseInput[value] = false;
			upMouse[value] = true;
			break;
		default:
			break;
		}
	}
}

bool Input::GetKey(Key keyCode)
{
	return inputs[static_cast<int>(keyCode)];
}

bool Input::GetKeyDown(Key keyCode)
{
	return downKeys[static_cast<int>(keyCode)];
}

bool Input::GetKeyUp(Key keyCode)
{
	return upKeys[static_cast<int>(keyCode)];
}

bool Input::GetMouse(Mouse button)
{
	return mouseInput[static_cast<int>(button)];
}

bool Input::GetMouseDown(Mouse button)
{
	return downMouse[static_cast<int>(button)];
}

bool Input::GetMouseUp(Mouse button)
{
	return upMouse[static_cast<int>(button)];
}

vec2 Input::GetMousePosition()
{
	return vec2(static_cast<float>(mouseX), static_cast<float>(mouseY));
}

void Input::SetCursorVisible(bool visible)
{
	if (visible)
		SDL_ShowCursor(1);
	else
		SDL_ShowCursor(0);
}