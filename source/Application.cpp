#include "Application.h"
#include "GlobalVar.h"
#include <raylib.h>

Application::Application() : mStateStack{State::Context()}
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO"); 
	SetTargetFPS(60); 

	registerStates(); 
	mStateStack.pushState(StateIDs::Home);
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
	mStateStack.draw(); 
	EndDrawing();
}

void Application::update(float dt)
{
	mStateStack.update(dt);
}

void Application::registerStates()
{

}

void Application::loadTextures()
{

}

void Application::loadFonts()
{
	std::string BASE_PATH = "assets/Fonts/"; 
	FontHolder::getInstance().load(FontID::Roboto, BASE_PATH + "Roboto-Medium.ttf");
}
