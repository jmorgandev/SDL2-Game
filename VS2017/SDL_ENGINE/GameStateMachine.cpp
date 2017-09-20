#include "GameStateMachine.h"

GameStateMachine* GameStateMachine::instance() {
	static GameStateMachine gameStateMachine_instance;
	return &gameStateMachine_instance;
}

//Push a Gamestate ontop of the GameState stack, useful for pause states
void GameStateMachine::pushState(GameState* pState) {
	m_gameStates.push_back(pState);
	m_gameStates.back()->onEnter();
}

//Pop a Gamestate from the top of the GameState stack, useful for pause states
void GameStateMachine::popState() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->onExit();
		delete m_gameStates.back();
		m_gameStates.pop_back();
	}
}

//Change the current game state
//Clear the gamestate stack depending on the loaded state
void GameStateMachine::changeState(GameState* pState) {
	if (!m_gameStates.empty()) {
		if (m_gameStates.back()->getStateID() == pState->getStateID()) return;
		switch (pState->onEnter()) {
		case STATE_EXIT: popState(); break;
		case STATE_CLEAN:
			if (!m_gameStates.empty()) {
				for (std::vector<GameState*>::iterator it = m_gameStates.begin(); it != m_gameStates.end(); it++) {
					(*it)->onExit();
					delete *it;
				}
				m_gameStates.clear();
			}
			break;
		case STATE_ERROR:
			printf("ERROR: Could not change state to %s!", pState->getStateID().c_str());
			return;
		}
		m_gameStates.push_back(pState);
	}
	else {
		if (pState->onEnter() == STATE_ERROR) {
			printf("ERROR: Could not change state to %s!", pState->getStateID().c_str());
			return;
		}
		m_gameStates.push_back(pState);
	}
}

//Update the gamestate on the top of the stack
void GameStateMachine::update() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->update();
	}
}

//Render the gamestate on the top of the stack
void GameStateMachine::render() {
	if (!m_gameStates.empty()) {
		m_gameStates.back()->render();
	}
}

//Clean every gamestate still loaded in
void GameStateMachine::clean() {
	while (!m_gameStates.empty()) {
		m_gameStates.back()->onExit();
		delete m_gameStates.back();
		m_gameStates.pop_back();
	}
}

//Return the current game state ID
std::string GameStateMachine::getCurrentID() {
	if (!m_gameStates.empty()) return m_gameStates.back()->getStateID();
	else return "NULL";
}