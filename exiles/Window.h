#pragma once

#include <string>

#include <SDL2/SDL_video.h>

#include "Math.h"

class Window
{
public:
	// �������������� SDL, ������ ���� � ������������� ��������� ���������,
	// �������������� �������� OpenGL � glew
	Window(const std::string& title, int width, int height);

	// ������� �������� OpenGL, ��������� ���� � ������ ��������� SDL 
	~Window();

	// �������� ���� ������, �������� � ������� SetClearColor
	void Clear();

	// ��������� ������ ����, ������ �� ������������
	void Display();

	// ������������� ������� ������� ������������ �������� ������ ���� ����
	void SetMousePosition(int x, int y);

	// ���������� ������� ������� ������� ������������ �������� ������ ���� ����
	ivec2 GetMousePosition();

	// ���������� ������ SDL_Window
	SDL_Window* GetSDLWindow() { return m_window; }

	// ���������� ������� ������� OpenGL
	SDL_GLContext* GetOpenGLContext() { return &m_context; }

	// ������������� ��������� �������
	void SetCursorVisible(bool visible);

	// ��������� ������ ������� ������
	//@ ��� ��������� ������ ���� ���������� �� ������� ������
	//@ ��� ������ �� ������ ������� ������ ������ ���� �� ����������
	void SetFullscreenEnabled(bool fullscreen);

	// ���������� �� ���� � ������ ������� ������
	bool IsFullscreenEnabled() const { return m_isFullscreen; }

	// ��������� ������������ �������������
	void SetVSyncEnabled(bool vsync);

	// ������� �� ����� ������������ �������������
	bool IsVSyncEnabled() const { return m_isVsyncEnabled; }

	// ������ ��������� ���� �� ���������
	void SetTitle(const std::string& title);

	// ���������� ������� ��������� ����
	std::string GetTitle() { return m_title; }

	// ������������� ������� ����
	void SetSize(int width, int height);

	// ���������� ������� ������� ����
	ivec2 GetSize() const { return m_size; }

	// ���������� ��������� ������ ���� � ��� ������
	float GetAspect() { return m_aspect; }

	// ������������� ���� ������� ����
	//@ ����� �������� ����� � ������� ������ ������� glClearColor()
	//TODO: ��������� ��� � ���� ����
	void SetClearColor(const vec4& color);

	// ���������� ������� ���� ������� ����
	//@ ���������� ������ ����, �������� � ������� SetClearColor()
	//TODO: ��������� ��� � ���� ����
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