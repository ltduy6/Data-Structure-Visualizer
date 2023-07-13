#include "Application.h"
#include "../source/Helper/GlobalVar.h"
#include <raylib.h>

Application::Application() : mStateStack{State::Context()}
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO"); 
	SetTargetFPS(60); 

	this->loadFonts();
	this->loadColor();

	registerStates(); 
	mStateStack.pushState(StateIDs::AVL);
}

Application::~Application()
{
	CloseWindow();
}

void Application::run()
{
	while (!WindowShouldClose())
	{
		update(GetFrameTime()); 
		render();
	}
}

void Application::render()
{
	BeginDrawing(); 
	ClearBackground(WHITE);
	mStateStack.draw(); 
	EndDrawing();
}

void Application::update(float dt)
{
	mStateStack.update(dt);
}

void Application::registerStates()
{
	this->mStateStack.registerState<BSTState>(StateIDs::BST); 
	this->mStateStack.registerState<AVLState>(StateIDs::AVL);
}

void Application::loadTextures()
{

}

void Application::loadFonts()
{
	std::string BASE_PATH = "assets/Fonts/"; 
	FontHolder::getInstance().load(FontID::Roboto, BASE_PATH + "Roboto-Medium.ttf");
}

void Application::loadColor()
{
	ColorSetting::GetInstance().load();
}
