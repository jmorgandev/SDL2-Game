#ifndef CAMERA_H
#define CAMERA_H

#include "Vector2.h"
#include <SDL.h>

//Game Camera Class
class Camera {
public:
	static Camera* instance();

	void update(Vector2f velocity);

	void setTarget(Vector2f* target, Vector2f* targetScale);
	void setPosition(const Vector2f& position) { m_position = position; }
	Vector2f getPosition() { return m_position; }
	void scrollCamera(Vector2f velocity) { m_position += velocity; }
	void centerView();
	
	bool inBounds(SDL_Rect* object);

private:
	Camera();
	~Camera(){}
	Vector2f m_position;
	Vector2f* m_target;
	Vector2f* m_targetScale;
};

#endif