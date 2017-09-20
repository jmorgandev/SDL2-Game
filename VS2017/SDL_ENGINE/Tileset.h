#ifndef TILESET_H
#define TILESET_H

#include <string>
//Tileset struct
struct Tileset {
	int firstGridID;
	int tileW;
	int tileH;
	int width;
	int height;
	int columns;
	int tileSize;
	std::string name;
};

#endif