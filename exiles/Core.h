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
	static void Run();
	static void Stop();

	template<class T, class ...Args>
	static void Push(Args&&... args) {
		auto state = std::unique_ptr<T>(new T(std::forward<Args>(args)...));
		state->OnInit();
		m_states.push(std::move(state));
	}

	template<class T, class ...Args>
	static void ChangeState(Args&&... args) {
		PopState();
		Push<T>(std::forward(args)...);
	}

	static void PopState();

	static State* PeekState();
private:
	static std::stack<std::unique_ptr<State>> m_states;
	static bool m_isRunning;
};