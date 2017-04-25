#pragma once

#include <memory>
#include <stack>

#include "AssetManager.h"
#include "Window.h"
#include "Input.h"
#include "State.h"
#include "Math.h"
#include "Log.h"

class Core
{
public:
	// ������ ���� � ��������� ����������� ������� ����������� �� Config
	static void Init(const std::string& title);

	// ��������� �������� ���� ����
	static void Run();

	// ������������� ���� ����
	static void Stop();

	static Window* GetWindow() { return m_window.get(); }

	// ��������� ����� �� ������� �����. �������� � �� OnInit
	template<class T, class ...Args>
	static void Push(Args&&... args) {
		static_assert(std::is_base_of<State, T>::value, "Core::Push template argument must be the child class of \"State\" class");

		auto state = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		state->OnInit();
		m_states.push(std::move(state));
	}

	// ������� ������� �����, � ��������� �����
	template<class T, class ...Args>
	static void ChangeState(Args&&... args) {
		PopState();
		Push<T>(std::forward(args)...);
	}

	// ������� ������� �����
	static void PopState();

	// ���������� ������� ����� ��� nullptr ���� ���� ������
	static State* PeekState();
private:
	static void HandleEvents();

	static std::stack<std::unique_ptr<State>> m_states; // �����
	
	static std::unique_ptr<Window> m_window;

	static bool m_isRunning;
};