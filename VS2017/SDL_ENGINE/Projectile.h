#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "SDLGameObject.h"


//Projectile Gameobject
class Projectile : public SDLGameObject {
public:
	Projectile(){ m_tag = "PROJECTILE"; }
	virtual ~Projectile(){}

	virtual void load(const LoadParameters parameters, Vector2f direction, float speed, std::string tag);

	virtual void draw();
	virtual void update(){ SDLGameObject::update(); }
	virtual void clean(){}

	void setDirection(int x, int y) { m_velocity.setX(x*m_speed); m_velocity.setY(y*m_speed); }
	void setSpeed(int speed) { m_speed = speed; }

	virtual void collision(std::string tag);
	virtual std::string getTag(){ return m_tag; }
	virtual bool toRemove(){ return m_destroyed; }

private:
	bool m_destroyed;
	float m_speed;
	std::string m_tag;
};

#endif