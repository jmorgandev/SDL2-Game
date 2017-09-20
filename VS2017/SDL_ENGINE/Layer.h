#ifndef LAYER_H
#define LAYER_H

#include "Vector2.h"
class Level;

enum LayerType { LAYER_TILE, LAYER_COLLISION, LAYER_OBJECT };

//Layer abstract base class for storing gameobjects and tiles
class Layer {
public:

	virtual ~Layer(){};

	virtual void render() = 0;
	virtual void update() = 0;
	virtual void clean() = 0;
	virtual LayerType getType(){ return m_type; }
	virtual void setType(LayerType type) { m_type = type; }

	virtual void setPosition(Vector2f pos){ m_position = pos; }
	Vector2f getPosition() { return m_position; }

protected:
	LayerType m_type;

	Vector2f m_position;
};

#endif