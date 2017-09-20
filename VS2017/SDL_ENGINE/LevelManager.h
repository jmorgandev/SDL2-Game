#ifndef LEVEL_MANAGER_H
#define LEVEL_MANAGER_H

#include <string>
#include <map>
#include "Level.h"
#include "LevelParser.h"


//Class that handles all available levels and switches between them on request
class LevelManager {
public:
	static LevelManager* instance();

	bool parseLocationFile(char* fileName);
	bool loadLevel(std::string id);
	bool changeLevel(std::string id, int x, int y);

	void update();
	void render();
	void clean();

	Level* getCurrentLevel() { return m_currentLevel; }

private:
	LevelManager();
	
	int m_playerHealthData;

	std::map<std::string, std::string> m_levelFiles;

	Level* m_currentLevel;
};

#endif