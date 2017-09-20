#include "LevelManager.h"
#include "tinyxml.h"
#include "GameStateMachine.h"
#include "GameOverState.h"
#include "VictoryMenuState.h"
#include "Camera.h"

LevelManager* LevelManager::instance() {
	static LevelManager levelManager_instance;
	return &levelManager_instance;
}

LevelManager::LevelManager() {
	m_currentLevel = NULL;
}

//Parse the XML file containing all Level fileNames
bool LevelManager::parseLocationFile(char* fileName) {
	TiXmlDocument XML_FILE;

	if (!XML_FILE.LoadFile(fileName)) {
		printf("ERROR: Could not load %s\n", fileName);
		printf("XML ERROR: %s\n", XML_FILE.ErrorDesc());
		return false;
	}

	TiXmlElement* pRoot = XML_FILE.RootElement();

	for (TiXmlElement* e = pRoot->FirstChildElement(); e != NULL; e = e->NextSiblingElement()) {
		std::string id = e->Attribute("ID");
		std::string file_directory = e->Attribute("filename");

		m_levelFiles[id] = file_directory;
	}

	return true;
}

//Load a Level using a fileName from the XML list
bool LevelManager::loadLevel(std::string id) {
	Level* newLevel;
	LevelParser levelParser;
	newLevel = levelParser.parseLevel(m_levelFiles[id].c_str());
	if (newLevel == NULL) return false;

	if (m_currentLevel != NULL) {
		m_currentLevel->clean();
		delete m_currentLevel;
	}
	
	m_currentLevel = newLevel;
	
	return true;
}

//Change the current level, and set the players new position
//To mimic a smooth transition
bool LevelManager::changeLevel(std::string id, int x, int y){
	m_playerHealthData = m_currentLevel->getPlayer()->getHealth();
	int row = m_currentLevel->getPlayer()->getCurrentRow();
	m_currentLevel->setPlayer(NULL);

	if (!loadLevel(id)) return false;

	m_currentLevel->getPlayer()->setHealth(m_playerHealthData);
	m_currentLevel->getPlayer()->getPosition().setX(x);
	m_currentLevel->getPlayer()->getPosition().setY(y);
	m_currentLevel->getPlayer()->setCurrentRow(row);

	Camera::instance()->centerView();

	return true;
}

//Update the current level
//Change to GameOver or Victory State depending on player checks
void LevelManager::update() {
	m_currentLevel->update();
	if (m_currentLevel->getPlayer() == NULL) {
		GameStateMachine::instance()->changeState(new GameOverState);
	}
	else if (m_currentLevel->getPlayer()->isVictory()) {
		GameStateMachine::instance()->changeState(new VictoryMenuState);
	}
}

//Render the current level
void LevelManager::render() {
	m_currentLevel->render();
}

//Clean the current level
void LevelManager::clean() {
	m_currentLevel->clean();
	delete m_currentLevel;
	m_currentLevel = NULL;
}

