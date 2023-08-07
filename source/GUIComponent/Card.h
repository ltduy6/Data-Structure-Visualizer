#pragma once
#include "Component.h"
#include "../States/StateIdentifiers.h"
#include "../ResourceHolder/FontHolder.h"
#include "../ResourceHolder/TextureHolder.h"
#include "../Helper/Helper.h"
#include "../Helper/GlobalVar.h"

#include <functional>
#include <map>

namespace GUI {
	class Card : public Component
	{
	public:
		Card(); 
		~Card();
	public:
		void draw(Vector2 base); 
		void update(float dt);
		void SetLink(std::function<void(StateIDs)> link);
		void SetCard(StateIDs stateID, std::string title, TextureID textureID);
		bool getHoverStatus() const;
	private:
		bool DrawImage(Vector2 base);
		bool DrawTitle(Vector2 base);
	private:
		Font font{FontHolder::getInstance().get(FontID::Roboto_Bold)};
		std::string name;
		std::function<void(StateIDs)> toLink; 
		StateIDs stateID;
		Texture2D target;
	private:
		std::map<std::string, Rectangle> hoverBounds; 
		bool isHover{ false };
	};
}

