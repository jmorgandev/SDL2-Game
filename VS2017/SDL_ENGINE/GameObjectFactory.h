#ifndef GAMEOBJECT_FACTORY_H
#define GAMEOBJECT_FACTORY_H

#include <string>
#include <map>

#include "BaseCreator.h"

//GameObject factory class for data driven design
class GameObjectFactory {
public:
	static GameObjectFactory* instance();

	bool registerType(std::string ID, BaseCreator* pCreator);

	void clean();

	GameObject* create(std::string ID);

private:
	GameObjectFactory(){}
	std::map<std::string, BaseCreator*> m_creators;
};

#endif