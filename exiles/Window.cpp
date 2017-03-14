#include "Window.h"

#include <GL\glew.h>
#include <SDL2\SDL.h>

std::string Window::m_title;
float Window::m_aspect = 0;
ivec2 Window::m_size;
vec3 Window::m_clearColor = vec3(0.2f, 0.2f, 0.2f);
bool Window::m_isOpen = false;
bool Window::m_isFocused = true;
SDL_Window* Window::m_window = nullptr;
SDL_GLContext Window::m_context = 0;

void Window::Create(const std::string & title, int width, int height)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);

	SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE, 32);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);

	if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		throw std::runtime_error("Unable to init SDL2");
	}

	m_aspect = static_cast<float>(width) / static_cast<float>(height);
	m_size = ivec2(width, height);

	m_window = SDL_CreateWindow(title.c_str(), SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_OPENGL);
	if (!m_window) {
		throw std::runtime_error("Unable to create window");
	}

	m_context = SDL_GL_CreateContext(m_window);
	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Unable to init glew");
	}

	m_isOpen = true;
}

void Window::Close()
{
	SDL_GL_DeleteContext(m_context);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
	m_isOpen = false;
}

void Window::SetFullscreen(bool fullscreen)
{
	SDL_SetWindowFullscreen(m_window, static_cast<int>(fullscreen));
}

void Window::SetVSync(bool vsync)
{
	SDL_GL_SetSwapInterval(static_cast<int>(vsync));
}

void Window::Clear()
{
	glClearColor(m_clearColor.x, m_clearColor.y, m_clearColor.z, 1.0f);
	glViewport(0, 0, m_size.x, m_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Clear(float r, float g, float b, float a)
{
	glClearColor(r, g, b, a);
	glViewport(0, 0, m_size.x, m_size.y);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::Display()
{
	SDL_GL_SwapWindow(m_window);
}

void Window::SetTitle(const std::string & title)
{
	SDL_SetWindowTitle(m_window, title.c_str());
}

void Window::SetSize(int width, int height)
{
	SDL_SetWindowSize(m_window, width, height);
	m_aspect = static_cast<float>(width) / static_cast<float>(height);
}

void Window::SetMousePosition(int x, int y)
{
	SDL_WarpMouseInWindow(m_window, x, y);
}

ivec2 Window::GetMousePosition()
{
	ivec2 mousePosition;
	SDL_GetMouseState(&mousePosition.x, &mousePosition.y);
	return mousePosition;
}
