#pragma once

#include <string>

#include <SDL2/SDL_video.h>

#include "Math.h"

class Window
{
public:
	static void Create(const std::string& title, int width, int height);
	static void Close();

	static void SetFullscreen(bool fullscreen);
	static void SetVSync(bool vsync);

	static void Clear();
	static void Clear(float r, float g, float b, float a);
	static void Display();

	static void SetTitle(const std::string& title);
	static std::string GetTitle() { return m_title; }

	static void SetSize(int width, int height);
	static ivec2 GetSize() { return m_size; }
	static float GetAspect() { return m_aspect; }

	static bool IsOpen() { return m_isOpen; }
	static bool IsFocused() { return m_isFocused; }

	static void SetClearColor(const vec3& color) { m_clearColor = color; }
	static vec3 GetClearColor() { return m_clearColor; }

	static void SetMousePosition(int x, int y);
	static ivec2 GetMousePosition();
private:
	friend class Input;

	static std::string m_title;

	static ivec2 m_size;
	static float m_aspect;

	static vec3 m_clearColor;

	static bool m_isOpen;
	static bool m_isFocused;

	static SDL_Window* m_window;
	static SDL_GLContext m_context;
};