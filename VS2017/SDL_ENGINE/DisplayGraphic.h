#ifndef DISPLAYGRAPHIC_H
#define DISPLAYGRAPHIC_H

#include "SDLGameObject.h"
#include "BaseCreator.h"
#include "Player.h"


//Game HUD/GUI class
class DisplayGraphic : public SDLGameObject{
public:
	DisplayGraphic(){}

	virtual void load(const LoadParameters parameters);

	void update();
	void draw();
	void clean();

	void setPlayer(Player* pPlayer) { m_playerRef = pPlayer; }
	
private:
	SDLGameObject* m_heartObject;
	Player* m_playerRef;
	int m_heartAmount;

	int m_hitTimer;
	int m_maxTimer;
	bool m_hit;
};

class DisplayGraphicCreator : public BaseCreator {
public:
	GameObject* createGameObject() const { return new DisplayGraphic(); }
};

#endif