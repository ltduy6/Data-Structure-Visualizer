#pragma once
#include "Component.h"
#include "../States/StateIdentifiers.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/GlobalVar.h"
#include "../Helper/Helper.h"

#include <functional>
#include <map>
#include <raylib.h>

namespace GUI {
	class NavigationBar : public Component
	{
	public:
		static constexpr float textSize = 36;
		static constexpr float HEIGHT = 50;
		static constexpr float pading = 7;
	public:
		NavigationBar(); 
		~NavigationBar();
	public:
		void draw(Vector2 base = { 0, 0 });
		void update(float dt);
		bool getHoverStatus() const;
	public:
		void InsertTitle(StateIDs stateID, std::string titleName);
		void SetDirectLink(std::function<void(StateIDs)> link);
		void SetActiveTitle(StateIDs stateID);
	private:
		StateIDs DrawTitles();
		bool DrawSetting();
		bool DrawLogo();
		void checkHover();
	private:
		class TitleInfor {
			StateIDs stateID; 
			std::string titleName;
		};
		std::function<void(StateIDs)> toLink;
		std::map<StateIDs, std::string> mTitles;
		std::map<std::string, Rectangle> hoverBounds;

		StateIDs activeTitle;
	private:
		Font fontDefault{ FontHolder::getInstance().get(FontID::Inter) };
		Font fontBold{ FontHolder::getInstance().get(FontID::Roboto_Bold) };
		bool hasTitle{ false };
		bool isHover{ false };
	};
}
