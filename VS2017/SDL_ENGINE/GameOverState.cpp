#include "GameOverState.h"
#include "MainMenuState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Game.h"
#include "Button.h"
#include "PlayState.h"


#include "StateParser.h"

#include <stdio.h>

const std::string GameOverState::s_stateID = "GAMEOVER";

//Update all gameobjects in state
void GameOverState::update() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (GameStateMachine::instance()->getCurrentID() != s_stateID) break;
		else m_gameObjects[i]->update();
	}
}

//Render all gameobjects in state
void GameOverState::render() {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Parse the current state from the XML state file, return ERROR if sometihng went wrong
int GameOverState::onEnter() {
	StateParser stateParser;
	if (!stateParser.parseState("data/STATE_DATA.xml", s_stateID, &m_textureIDs, &m_gameObjects)) return STATE_ERROR;

	m_callbacks.push_back(s_restartGame);
	m_callbacks.push_back(s_exitToMenu);
	m_callbacks.push_back(s_exitProgram);

	setCallbacks(m_callbacks);

	return STATE_CLEAN;
}

//Clean up everything
void GameOverState::onExit() {
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

//Set callback functions for the StateParser to use
void GameOverState::setCallbacks(const std::vector<Callback>& callbacks) {
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (dynamic_cast<Button*>(m_gameObjects[i])) {
			Button* pButton = dynamic_cast<Button*>(m_gameObjects[i]);
			pButton->setCallback(callbacks[pButton->getCallbackID()]);
		}
	}
}


void GameOverState::s_restartGame() {
	GameStateMachine::instance()->changeState(new PlayState);
}

void GameOverState::s_exitToMenu() {
	GameStateMachine::instance()->changeState(new MainMenuState);
}

void GameOverState::s_exitProgram() {
	Game::instance()->quit();
}