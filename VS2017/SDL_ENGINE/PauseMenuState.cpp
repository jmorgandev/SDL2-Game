#include "PauseMenuState.h"

#include "MainMenuState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"

#include "StateParser.h"

#include <stdio.h>

const std::string PauseMenuState::s_stateID = "PAUSE";

//Update all gameobjects in state
void PauseMenuState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (GameStateMachine::instance()->getCurrentID() != s_stateID) break;
		else m_gameObjects[i]->update();
	}
}

//Render all gameobjects in state
void PauseMenuState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Parse the XML state file
int PauseMenuState::onEnter() {
	StateParser stateParser;
	if (!stateParser.parseState("data/STATE_DATA.xml", s_stateID, &m_textureIDs, &m_gameObjects)) return STATE_ERROR;

	m_callbacks.push_back(s_resumeGame);
	m_callbacks.push_back(s_exitToMenu);

	setCallbacks(m_callbacks);

	return STATE_EXIT;
}

//Clean up everything
void PauseMenuState::onExit() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		(*it)->clean();
		delete *it;
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDs.size(); i++) {
		TextureManager::instance()->clearTexture(m_textureIDs[i]);
	}
	m_textureIDs.clear();
}

//Set callbacks for the Levelparser to use
void PauseMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (dynamic_cast<Button*>(m_gameObjects[i])) {
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void PauseMenuState::s_resumeGame() {
	GameStateMachine::instance()->popState();
}

void PauseMenuState::s_exitToMenu() {
	GameStateMachine::instance()->changeState(new MainMenuState);
}