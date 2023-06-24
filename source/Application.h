#ifndef APPLICATION_H
#define APPLICATION_H

#include "ResourceHolder/TextureHolder.h"; 
#include "ResourceHolder/FontHolder.h";
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
private:
	StateStack mStateStack;
};
#endif

