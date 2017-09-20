#ifndef COLLISION_H
#define COLLISION_H

#include <SDL.h>

const static int s_buffer = 4;

//Static class for calculating box collision
class Collision {
public:
	static bool RectRect(SDL_Rect* A, SDL_Rect* B) {
		return(abs(A->x - B->x) * 2 < (A->w + B->w)) &&
			(abs(A->y - B->y) * 2 < (A->h + B->h));
	}
};
#endif