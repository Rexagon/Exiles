#include "Core.h"

#include <SDL2\SDL.h>

std::stack<std::unique_ptr<State>> Core::m_states;
std::unique_ptr<Window> Core::m_window;
bool Core::m_isRunning = false;

void Core::Init(const std::string & title)
{
	if (m_isRunning == true) {
		throw std::logic_error("Unable to init core after running");
	}

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

	//TODO: load window from config
	m_window = std::make_unique<Window>(title, 1024, 768);
}

void Core::Run()
{
	if (m_window == nullptr) {
		throw std::logic_error("Unable to run core without a window");
	}

	m_isRunning = true;
	unsigned long long lastTime = SDL_GetPerformanceCounter();
	while (m_isRunning) {
		HandleEvents();

		unsigned long long currentTime = SDL_GetPerformanceCounter();
		float dt = static_cast<float>(currentTime - lastTime) / SDL_GetPerformanceFrequency();
		lastTime = currentTime;

		State* currentState;
		if (currentState = PeekState()) {
			currentState->OnUpdate(dt);
		}

		if (currentState = PeekState()) {
			currentState->OnDraw(dt);
		}

		m_window->Display();
	}

	AssetManager::Clear();

	while (!m_states.empty()) {
		PopState();
	}

	m_window.reset();
	SDL_Quit();
}

void Core::Stop()
{
	m_isRunning = false;
}

void Core::PopState()
{
	if (!m_states.empty()) {
		m_states.top()->OnClose();
		m_states.pop();
	}
}

State * Core::PeekState()
{
	if (!m_states.empty()) {
		return m_states.top().get();
	}
	else {
		Stop();
		return nullptr;
	}
}

void Core::HandleEvents()
{
	Input::Update();

	SDL_Event e;

	while (SDL_PollEvent(&e)) {
		int value = 0;
		State* currentState = PeekState();

		switch (e.type) {
		case SDL_QUIT:
			Core::Stop();
			break;
		case SDL_WINDOWEVENT_FOCUS_GAINED:
			if (currentState) {
				currentState->OnFocusGained();
			}
			break;
		case SDL_WINDOWEVENT_FOCUS_LOST:
		case SDL_WINDOWEVENT_HIDDEN:
			if (currentState) {
				currentState->OnFocusLost();
			}
			break;
		case SDL_MOUSEMOTION:
			Input::m_mousePosition = ivec2(e.motion.x, e.motion.y);
			break;
		case SDL_KEYDOWN:
			Input::m_currentKeysState[e.key.keysym.scancode] = true;
			break;
		case SDL_KEYUP:
			Input::m_currentKeysState[e.key.keysym.scancode] = false;
			break;
		case SDL_MOUSEBUTTONDOWN:
			Input::m_currentMouseButtonsState[e.button.button] = true;
			break;
		case SDL_MOUSEBUTTONUP:
			Input::m_currentMouseButtonsState[e.button.button] = false;
			break;
		default:
			break;
		}
	}
}
