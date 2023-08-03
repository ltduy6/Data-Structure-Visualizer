#include "HomeState.h"

HomeState::HomeState(StateStack& stack, Context context) : State(stack, context), hasCards(true)
{
	this->InitCards();
}

void HomeState::draw()
{
	this->mCards.draw();
	this->navBar.draw();
	this->DrawLogo();
}

bool HomeState::update(float dt)
{
	this->navBar.update(dt);
	if (this->mCards.getHoverStatus() == false && this->navBar.getHoverStatus() == false)
		SetMouseCursor(MOUSE_CURSOR_DEFAULT);
	return true;
}

void HomeState::InitCards()
{
	this->mCards.SetPos({ 200, -100 });
	CreateCard(StateIDs::AVL, "AVL Tree", TextureID::AVL_Card, Vector2{ 100, 500 });
	CreateCard(StateIDs::Btree, "2-3-4 Tree", TextureID::Btree, Vector2{ 650, 500 });
	CreateCard(StateIDs::Heap, "Binary Heap", TextureID::Heap, Vector2{ 1200, 500 });
	CreateCard(StateIDs::Graph, "Graph", TextureID::Graph, Vector2{ 100, 1100 });
	CreateCard(StateIDs::Hash, "Hash Table", TextureID::Hash, Vector2{ 650,  1100 });
	CreateCard(StateIDs::Trie, "Trie", TextureID::Trie, Vector2{ 1200, 1100 });
}

void HomeState::CreateCard(StateIDs stateID, std::string title, TextureID textureID, Vector2 pos)
{
	std::shared_ptr<GUI::Card> card(new GUI::Card());
	card->SetPos(pos);
	card->SetLink([this](StateIDs stateID) {
		requestStackPop();
		requestStackPush(stateID);
		});
	card->SetCard(stateID, title, textureID);
	this->mCards.pack(card);
}

void HomeState::DrawLogo()
{
	Font font{ FontHolder::getInstance().get(FontID::Handjet) };
	Color color = { 255, 102, 102, 255 };
	std::string text = "DATA STRUCTURE VISUALIZER";
	float textSize = 120;
	Vector2 textBound = MeasureTextEx(font, text.c_str(), textSize, 10);
	Vector2 pos = (Vector2{ Constant::WINDOW_WIDTH, 400 } - textBound) / 2;

	DrawTextEx(font, text.c_str(), pos, textSize, 10, color);
}
