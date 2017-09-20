#include "VictoryMenuState.h"

#include "MainMenuState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"

#include "StateParser.h"

#include <stdio.h>

const std::string VictoryMenuState::s_stateID = "VICTORY";

//Update gameobjects in state
void VictoryMenuState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (GameStateMachine::instance()->getCurrentID() != s_stateID) break;
		else m_gameObjects[i]->update();
	}
}

//Render gameobjects in state
void VictoryMenuState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Parse state using state XML file
int VictoryMenuState::onEnter() {
	StateParser stateParser;
	if (!stateParser.parseState("data/STATE_DATA.xml", s_stateID, &m_textureIDs, &m_gameObjects)) return STATE_ERROR;

	m_callbacks.push_back(s_exitToMenu);
	m_callbacks.push_back(s_exitGame);

	setCallbacks(m_callbacks);

	return STATE_EXIT;
}

//Clean up everything
void VictoryMenuState::onExit() {
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

void VictoryMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (dynamic_cast<Button*>(m_gameObjects[i])) {
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void VictoryMenuState::s_exitToMenu() {
	GameStateMachine::instance()->changeState(new MainMenuState);
}

void VictoryMenuState::s_exitGame() {
	Game::instance()->quit();
}