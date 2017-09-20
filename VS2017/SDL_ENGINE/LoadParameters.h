#ifndef LOADPARAMETERS_H
#define LOADPARAMETERS_H

#include <string>

//Parameters to pass into every gameobject for loading
class LoadParameters {
public:

	LoadParameters(int x, int y, int width, int height, std::string textureID, int currentRow = 0, int currentFrame = 0, int callbackID = 0) :
		m_x(x), m_y(y), m_width(width), m_height(height), m_textureID(textureID),
		m_currentRow(currentRow), m_currentFrame(currentFrame), m_callbackID(callbackID){}

	int getX() const { return m_x; }
	int getY() const { return m_y; }
	int getWidth() const { return m_width; }
	int getHeight() const { return m_height; }
	int getCurrentRow() const { return m_currentRow; }
	int getCurrentFrame() const { return m_currentFrame; }
	std::string getTextureID() const { return m_textureID; }
	int getCallbackID() const { return m_callbackID; }

private:
	int m_x;
	int m_y;

	int m_width;
	int m_height;

	int m_currentRow;
	int m_currentFrame;

	int m_callbackID;

	std::string m_textureID;
};

#endif