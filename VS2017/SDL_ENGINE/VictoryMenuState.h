#ifndef VICTORY_MENU_STATE_H
#define VICTORY_MENU_STATE_H

#include "MenuState.h"

//Gamestate when the player has won
class VictoryMenuState : public MenuState {
public:
	virtual void update();
	virtual void render();

	virtual int onEnter();
	virtual void onExit();

	virtual std::string getStateID() const { return s_stateID; }

private:
	static const std::string s_stateID;

	virtual void setCallbacks(const std::vector<Callback>& callbacks);

	static void s_exitToMenu();
	static void s_exitGame();
};

#endif