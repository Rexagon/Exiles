#include "Core.h"

std::stack<std::unique_ptr<State>> Core::m_states;
std::unique_ptr<sf::RenderWindow> Core::m_window;
bool Core::m_isRunning = false;

void Core::Init(const std::string & title)
{
	if (m_isRunning == true) {
		throw std::logic_error("Unable to init core after running");
	}

	sf::ContextSettings settings;
	settings.depthBits = 24;
	settings.stencilBits = 8;
	//settings.antialiasingLevel = 4;
	settings.majorVersion = 3;
	settings.minorVersion = 3;

	m_window = std::make_unique<sf::RenderWindow>(sf::VideoMode(1024, 768), title, sf::Style::Default, settings);
	if (!m_window) {
		throw std::runtime_error("Unable to create window");
	}

	m_window->setVerticalSyncEnabled(true);
	m_window->setActive(true);

	if (glewInit() != GLEW_OK) {
		throw std::runtime_error("Unable to init glew");
	}
}

void Core::Run()
{
	if (m_window == nullptr) {
		throw std::logic_error("Unable to run core without a window");
	}
	m_isRunning = true;

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);

	sf::Clock timer;
	while (m_isRunning) {
		HandleEvents();

		float dt = timer.restart().asSeconds();

		State* currentState;
		if (currentState = PeekState()) {
			currentState->m_gui.Update();
			currentState->OnUpdate(dt);
		}
		
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		if (currentState = PeekState()) {
			currentState->OnDraw(dt);

			m_window->pushGLStates();
			currentState->m_gui.Draw();
			m_window->popGLStates();
		}

		m_window->display();
	}

	AssetManager::Clear();

	while (!m_states.empty()) {
		PopState();
	}

	m_window->close();
	m_window.reset();
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

	sf::Event e;

	while (m_window->pollEvent(e)) {
		int value = 0;
		State* currentState = PeekState();

		switch (e.type) {
		case sf::Event::Closed:
			Core::Stop();
			break;
		case sf::Event::GainedFocus:
			if (currentState) {
				currentState->OnFocusGained();
			}
			break;
		case sf::Event::LostFocus:
			if (currentState) {
				currentState->OnFocusLost();
			}
			break;
		case sf::Event::MouseMoved:
			Input::m_mousePosition = ivec2(e.mouseMove.x, e.mouseMove.y);
			break;
		case sf::Event::KeyPressed:
			if (e.key.code > -1 && e.key.code < sf::Keyboard::KeyCount) {
				Input::m_currentKeysState[e.key.code] = true;
			}
			break;
		case sf::Event::KeyReleased:
			if (e.key.code > -1 && e.key.code < sf::Keyboard::KeyCount) {
				Input::m_currentKeysState[e.key.code] = false;
			}
			break;
		case sf::Event::MouseButtonPressed:
			if (e.mouseButton.button > -1 && e.mouseButton.button < sf::Mouse::ButtonCount) {
				Input::m_currentMouseButtonsState[e.mouseButton.button] = true;
			}
			break;
		case sf::Event::MouseButtonReleased:
			if (e.mouseButton.button > -1 && e.mouseButton.button < sf::Mouse::ButtonCount) {
				Input::m_currentMouseButtonsState[e.mouseButton.button] = false;
			}
			break;
		default:
			break;
		}
	}
}
