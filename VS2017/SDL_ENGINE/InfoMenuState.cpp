#include "InfoMenuState.h"

#include "MainMenuState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"
#include "PlayState.h"

#include "StateParser.h"

#include <stdio.h>

const std::string InfoMenuState::s_stateID = "INFO";

//Update all gameobjects in state
void InfoMenuState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (GameStateMachine::instance()->getCurrentID() != s_stateID) break;
		else m_gameObjects[i]->update();
	}
}

//Render all gameobjects in state
void InfoMenuState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Parse the state using the XML state file
int InfoMenuState::onEnter() {
	StateParser stateParser;
	if (!stateParser.parseState("data/STATE_DATA.xml", s_stateID, &m_textureIDs, &m_gameObjects)) return STATE_ERROR;

	m_callbacks.push_back(s_playGame);

	setCallbacks(m_callbacks);

	return STATE_EXIT;
}

//Clean up everything
void InfoMenuState::onExit() {
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

//Set callbacks for the Stateparser to use
void InfoMenuState::setCallbacks(const std::vector<Callback>& callbacks) {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (dynamic_cast<Button*>(m_gameObjects[i])) {
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}

void InfoMenuState::s_playGame() {
	GameStateMachine::instance()->changeState(new PlayState);
}