#ifndef APPLICATION_H
#define APPLICATION_H

#include "ResourceHolder/TextureHolder.h"; 
#include "ResourceHolder/FontHolder.h";
#include "Helper/ColorSetting.h"
#include "States/BSTState.h"
#include "States/AVLState.h"
#include "States/BTreeState.h"
#include "States/HeapState.h"
#include "States/TrieState.h"
#include "States/GraphState.h"
#include "StateStack.h"

class Application
{
public:
	Application(); 
	~Application(); 
	void run(); 
private:
	void render();
	void update(float dt);
	void registerStates();
	void loadTextures(); 
	void loadFonts();
	void loadColor(); 
private:
	StateStack mStateStack;
};
#endif

