#include "Application.h"
#include "../source/Helper/GlobalVar.h"
#include <raylib.h>

Application::Application() : mStateStack{State::Context()}
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "DATA STRUCTURE VISUALIZER");
	SetTargetFPS(60); 

	this->loadFonts();
	this->loadTextures();
	this->loadColor();

	registerStates(); 
	mStateStack.pushState(StateIDs::Home);
}

Application::~Application()
{
	mStateStack.clearState();
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
	ClearBackground(ColorSetting::GetInstance().get(ColorThemeID::SCREEN_BACKGROUND));
	mStateStack.draw(); 
	EndDrawing();
}

void Application::update(float dt)
{
	mStateStack.update(dt);
}

void Application::registerStates()
{
	this->mStateStack.registerState<HomeState>(StateIDs::Home);
	this->mStateStack.registerState<AVLState>(StateIDs::AVL);
	this->mStateStack.registerState<BTreeState>(StateIDs::Btree); 
	this->mStateStack.registerState<HeapState>(StateIDs::Heap);
	this->mStateStack.registerState<TrieState>(StateIDs::Trie);
	this->mStateStack.registerState<GraphState>(StateIDs::Graph);
	this->mStateStack.registerState<HashState>(StateIDs::Hash);
}

void Application::loadTextures()
{
	std::string BASE_PATH = "assets/Textures/"; 
	TextureHolder::getInstance().load(TextureID::AVL_Card, BASE_PATH + "AVL_Card.png");
	TextureHolder::getInstance().load(TextureID::Btree, BASE_PATH + "Btree.png");
	TextureHolder::getInstance().load(TextureID::Graph, BASE_PATH + "Graph.png");
	TextureHolder::getInstance().load(TextureID::Hash, BASE_PATH + "Hash.png");
	TextureHolder::getInstance().load(TextureID::Heap, BASE_PATH + "Heap.png");
	TextureHolder::getInstance().load(TextureID::Trie, BASE_PATH + "Trie.png");
}

void Application::loadFonts()
{
	std::string BASE_PATH = "assets/Fonts/"; 
	FontHolder::getInstance().load(FontID::Roboto, BASE_PATH + "Roboto-Medium.ttf");
	FontHolder::getInstance().load(FontID::Roboto_Bold, BASE_PATH + "Roboto-Bold.ttf");
	FontHolder::getInstance().load(FontID::Inter, BASE_PATH + "Inter.ttf");
	FontHolder::getInstance().load(FontID::Courier, BASE_PATH + "CourierPrime-Regular.ttf");
	FontHolder::getInstance().load(FontID::Handjet, BASE_PATH + "Handjet-ExtraBold.ttf");
}

void Application::loadColor()
{
	ColorSetting::GetInstance().load();
}
