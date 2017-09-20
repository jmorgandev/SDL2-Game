#ifndef STATE_PARSER_H
#define STATE_PARSER_H

#include <vector>
#include "tinyxml.h"

class GameObject;


//Class for parsing states from the state XML file
class StateParser {
public:

	bool parseState(const char* stateFile, std::string stateID, std::vector<std::string> *pTextureIDs, std::vector<GameObject*> *pObjects);

private:
	void parseTextures(TiXmlElement* pRoot, std::vector<std::string> *pTextureIDs);
	void parseObjects(TiXmlElement* pRoot, std::vector<GameObject*> *pObjects);
};

#endif