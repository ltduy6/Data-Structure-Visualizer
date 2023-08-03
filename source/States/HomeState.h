#pragma once
#include "State.h"
#include "../ResourceHolder/TextureHolder.h"
#include "../GUIComponent/Container.h"
#include "../GUIComponent/Card.h"
#include "../Helper/GlobalVar.h"
#include "../GUIComponent/NavigationBar.h"

#include <string>

class HomeState : public State
{
public:
	HomeState(StateStack& stack, Context context);
	virtual void draw(); 
	virtual bool update(float dt);
private:
	void InitCards();
	void CreateCard(StateIDs stateID, std::string title, TextureID textureID, Vector2 pos);
	void DrawLogo();
private:
	GUI::NavigationBar navBar;
	GUI::Container mCards; 
	bool hasCards;
};

