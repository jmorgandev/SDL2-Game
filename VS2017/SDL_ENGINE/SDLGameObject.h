#ifndef SDLGAMEOBJECT_H
#define SDLGAMEOBJECT_H

#include <SDL.h>

#include "GameObject.h"


//GameObject base class with specific SDL function
class SDLGameObject : public GameObject {
public:
	SDLGameObject(){ m_drawable = true; }
	virtual ~SDLGameObject(){}

	virtual void load(const LoadParameters parameters);

	virtual void draw();
	virtual void update();
	virtual void clean(){}
	
	virtual void collision(std::string tag){}
	virtual std::string getTag(){ return "SDL_GAMEOBJECT"; }
	virtual bool toRemove(){ return false; }

	virtual Vector2f& getPosition(){ return m_position; }
	virtual Vector2f& getScale() { return m_scale; }
	virtual Vector2f& getVelocity() { return m_velocity; }

	void setDrawable(bool canDraw) { m_drawable = canDraw; }

protected:
	
	Vector2f m_position;
	Vector2f m_scale;

	Vector2f m_velocity;

	std::string m_textureID;
	SDL_RendererFlip m_flip;

	bool m_drawable;

	int m_currentRow, m_currentFrame;
};

#endif