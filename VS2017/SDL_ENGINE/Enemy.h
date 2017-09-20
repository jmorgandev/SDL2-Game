#ifndef ENEMY_H
#define ENEMY_H

#include "SDLGameObject.h"
#include "BaseCreator.h"
#include <vector>

//Enemy class
class Enemy : public SDLGameObject {
public:
	Enemy();
	virtual ~Enemy(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision(std::string tag);
	virtual std::string getTag(){ return "ENEMY"; }
	virtual bool toRemove(){ return m_dead; }

	int getHealth(){ return m_health; }

	SDL_Rect getCollisionBox() { return m_collider; }

private:
	SDL_Rect m_collider;

	Vector2f m_target;

	float m_speed;
	bool m_dead;
	bool m_found;
	int m_health;

	void attack();
	int m_attackTimer;
	int m_maxTimer;
};

class EnemyCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new Enemy(); }
};

#endif