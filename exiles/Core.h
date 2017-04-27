#pragma once

#include <memory>
#include <stack>

#include <GL/glew.h>

#include <SFML/Graphics.hpp>

#include "AssetManager.h"
#include "Input.h"
#include "State.h"
#include "Math.h"
#include "GUI.h"
#include "Log.h"

class Core
{
public:
	// Создаёт окно с указанным заголовкоми другими настройками из Config
	static void Init(const std::string& title);

	// Запускает основной цикл игры
	static void Run();

	// Останавливает цикл игры
	static void Stop();

	static sf::RenderWindow* GetWindow() { return m_window.get(); }

	// Добавляет сцену на вершину стэка. Вызывает у неё OnInit
	template<class T, class ...Args>
	static void Push(Args&&... args) {
		static_assert(std::is_base_of<State, T>::value, "Core::Push template argument must be the child class of \"State\" class");

		auto state = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		state->OnInit();
		m_states.push(std::move(state));
	}

	// Удаляет текущую сцену, и добавляет новую
	template<class T, class ...Args>
	static void ChangeState(Args&&... args) {
		PopState();
		Push<T>(std::forward(args)...);
	}

	// Удаляет текущую сцену
	static void PopState();

	// Возвращает текущую сцену или nullptr если стэк пустой
	static State* PeekState();
private:
	static void HandleEvents();

	static std::stack<std::unique_ptr<State>> m_states; // Сцены
	
	static std::unique_ptr<sf::RenderWindow> m_window;

	static bool m_isRunning;
};