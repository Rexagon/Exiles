#include "Window.h"

#include <GL\glew.h>
#include <SDL2\SDL.h>

Window::Window(const std::string & title, int width, int height)
{
	m_aspect = static_cast<float>(width) / static_cast<float>(height);
	m_size = ivec2(width, height);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (m_window == nullptr) {
		throw std::runtime_error("Unable to create window");
	}

	m_context = SDL_GL_CreateContext(m_window);
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Unable to init glew");
	}
}

Window::~Window()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
}

void Window::Clear()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Display()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(m_window, x, y);
}

ivec2 Window::GetMousePosition()
{
	ivec2 position;
	SDL_GetMouseState(&position.x, &position.y);
	return position;
}

void Window::SetCursorVisible(bool visible)
{
	SDL_ShowCursor(static_cast<int>(visible));
}

void Window::SetFullscreenEnabled(bool fullscreen)
{
	m_isFullscreen = fullscreen;
	SDL_SetWindowFullscreen(m_window, SDL_WINDOW_FULLSCREEN & m_isFullscreen);
}

void Window::SetVSyncEnabled(bool vsync)
{
	m_isVsyncEnabled = vsync;
	SDL_GL_SetSwapInterval(static_cast<int>(m_isVsyncEnabled));
}

void Window::SetTitle(const std::string & title)
{
	m_title = title;
	SDL_SetWindowTitle(m_window, m_title.c_str());
}

void Window::SetSize(int width, int height)
{
	m_size = ivec2(width, height);
	SDL_SetWindowSize(m_window, m_size.x, m_size.y);
}

void Window::SetClearColor(const vec4 & color)
{
	m_clearColor = color;
	glClearColor(m_clearColor.r, m_clearColor.g, m_clearColor.b, m_clearColor.a);
}
