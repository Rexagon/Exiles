#pragma once

#include <string>

#include <SDL2/SDL_video.h>

#include "Math.h"

class Window
{
public:
	// Инициализирует SDL, создаёт окно с неизменяемыми заданными размерами,
	// инициализирует контекст OpenGL и glew
	Window(const std::string& title, int width, int height);

	// Удаляет контекст OpenGL, закрывает окно и чистит состояние SDL 
	~Window();

	// Заливает окно цветом, заданным с помощью SetClearColor
	void Clear();

	// Обновляет буффер окна, выводя всё нарисованное
	void Display();

	// Устанавливает позицию курсора относительно верхнего левого края окна
	void SetMousePosition(int x, int y);

	// Возвращает текущую позицию курсора относительно верхнего левого края окна
	ivec2 GetMousePosition();

	// Возвращает объект SDL_Window
	SDL_Window* GetSDLWindow() { return m_window; }

	// Возвращает текущий контект OpenGL
	SDL_GLContext* GetOpenGLContext() { return &m_context; }

	// Устанавливает видимость курсора
	void SetCursorVisible(bool visible);

	// Установка режима полного экрана
	//@ при установке размер окна измениться до размера экрана
	//@ при выходе из режима полного экрана размер окна не измениться
	void SetFullscreenEnabled(bool fullscreen);

	// Находиться ли окно в режиме полного экрана
	bool IsFullscreenEnabled() const { return m_isFullscreen; }

	// Установка вертикальной синхронизации
	void SetVSyncEnabled(bool vsync);

	// Включён ли режим вертикальной синхронизации
	bool IsVSyncEnabled() const { return m_isVsyncEnabled; }

	// Меняет заголовок окна на указанный
	void SetTitle(const std::string& title);

	// Возвращает текущий заголовок окна
	std::string GetTitle() { return m_title; }

	// Устанавливает размеры окна
	void SetSize(int width, int height);

	// Возвращает текущие размеры окна
	ivec2 GetSize() const { return m_size; }

	// Возвращает отношение ширины окна к его высоте
	float GetAspect() { return m_aspect; }

	// Устанавливает цвет заливки окна
	//@ может меняться извне с помощью вызова функции glClearColor()
	//TODO: придумать как с этим быть
	void SetClearColor(const vec4& color);

	// Возвращает текущий цвет заливки окна
	//@ возвращает именно цвет, заданный с помощью SetClearColor()
	//TODO: придумать как с этим быть
	vec3 GetClearColor() const { return m_clearColor; }
private:
	std::string m_title;
	ivec2 m_size;
	float m_aspect;

	bool m_isFullscreen;
	bool m_isVsyncEnabled;
	vec4 m_clearColor;

	SDL_Window* m_window;
	SDL_GLContext m_context;
};