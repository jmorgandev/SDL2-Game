#ifndef PLAYER_H
#define PLAYER_H

#include "SDLGameObject.h"
#include "EventHandler.h"
#include "BaseCreator.h"
#include <vector>


//Player state, very important for the game

class Player : public SDLGameObject, public EventHandler {
public:
	Player();
	virtual ~Player(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw();
	virtual void update();
	virtual void clean();

	virtual void collision(std::string tag);
	virtual std::string getTag(){ return "PLAYER"; }
	virtual bool toRemove(){ return m_dead; }

	void setHealth(int h) { m_health = h; }
	int getHealth(){ return m_health; }

	SDL_Rect getCollisionBox() { return m_collider; }

	bool isVictory() { return m_victory; }
	void setVictory(bool v) { m_victory = v; }

	int getCurrentRow() { return m_currentRow; }
	void setCurrentRow(int i) { m_currentRow = i; }

private:
	SDL_Rect m_collider;

	float m_speed;
	bool m_dead;
	bool m_moving;
	int m_health;

	bool m_invulnerable;
	int m_maxTimer;
	int m_invulnerableTimer;

	bool m_victory;

	Vector2f m_direction;

	std::vector<SDL_Scancode> m_keyList;

	void OnKeyboardEvent(const SDL_KeyboardEvent& e);

	void doMovement();
};

class PlayerCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new Player(); }
};

#endif