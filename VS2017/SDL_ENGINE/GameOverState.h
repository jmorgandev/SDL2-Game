#ifndef GAMEOVER_STATE_H
#define GAMEOVER_STATE_H

#include "MenuState.h"

//GameOverState class to display the Game Over menu
class GameOverState : public MenuState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_restartGame();
	static void s_exitToMenu();
	static void s_exitProgram();
};

#endif