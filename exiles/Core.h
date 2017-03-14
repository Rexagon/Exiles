#pragma once

#include <memory>
#include <stack>

#include "Input.h"
#include "State.h"
#include "Log.h"
#include "Math.h"
#include "AssetManager.h"

class Core
{
public:
	// Запускает основной цикл игры
	static void Run();

	// Останавливает цикл игры
	static void Stop();

	// Добавляет сцену на вершину стэка. Вызывает у неё OnInit
	template<class T, class ...Args>
	static void Push(Args&&... args) {
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
	// Сцены
	static std::stack<std::unique_ptr<State>> m_states;
	static bool m_isRunning;
};