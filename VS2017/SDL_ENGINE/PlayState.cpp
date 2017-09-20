#include "PlayState.h"
#include "GameStateMachine.h"
#include "TextureManager.h"
#include "Game.h"
#include "PauseMenuState.h"
#include "StateParser.h"
#include "LevelParser.h"
#include "LevelManager.h"

const std::string PlayState::s_stateID = "PLAY";

//Update all gameobjects in state
void PlayState::update() {
	//if (GameStateMachine::instance()->getCurrentID() == s_stateID) m_currentLevel->update();
	if (GameStateMachine::instance()->getCurrentID() == s_stateID) LevelManager::instance()->update();
	for (int i = 0; i < m_gameObjects.size(); i++) {
		if (GameStateMachine::instance()->getCurrentID() != s_stateID) break;
		else m_gameObjects[i]->update();
	}
}

//Render all gameobjects in state
void PlayState::render() {
	//m_currentLevel->render();
	LevelManager::instance()->render();
	for (int i = 0; i < m_gameObjects.size(); i++) {
		m_gameObjects[i]->draw();
	}
}

//Parse the Level list XML file for all level fileNames, and load the starting level using the level manager
int PlayState::onEnter() {
		

	if (!LevelManager::instance()->parseLocationFile("data/LEVEL_LIST.xml")) return STATE_ERROR;
	if (!LevelManager::instance()->loadLevel("start")) return STATE_ERROR;

	StateParser stateParser;
	if (!stateParser.parseState("data/STATE_DATA.xml", s_stateID, &m_textureIDs, &m_gameObjects)) return STATE_ERROR;

	Game::instance()->addEventHandler(this);

	return STATE_CLEAN;
}

//Clean up everything
void PlayState::onExit() {
	for (std::vector<GameObject*>::iterator it = m_gameObjects.begin(); it != m_gameObjects.end(); it++) {
		(*it)->clean();
		delete *it;
	}
	m_gameObjects.clear();

	for (int i = 0; i < m_textureIDs.size(); i++) {
		TextureManager::instance()->clearTexture(m_textureIDs[i]);
	}
	m_textureIDs.clear();

	LevelManager::instance()->clean();

	Game::instance()->removeEventHandler(this);
}

//Pause if ESC key is pressed
void PlayState::OnKeyboardEvent(const SDL_KeyboardEvent &e) {
	if (e.state == SDL_PRESSED) {
		switch (e.keysym.scancode) {
		case SDL_SCANCODE_ESCAPE:
			if (GameStateMachine::instance()->getCurrentID() == "PLAY") GameStateMachine::instance()->pushState(new PauseMenuState);
			break;
		}
	}
}