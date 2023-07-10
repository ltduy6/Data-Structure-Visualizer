#pragma once

#include "Component.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"

#include <functional>
#include <vector>
#include <string>

namespace GUI {
	class Button : public Component
	{
	public: 
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<void()> CallBack;

		enum class TextAlignMent {
			Left, 
			Center, 
			Right,
			AlignmentCount
		};

	public:
		explicit Button(); 
		~Button(); 

		virtual void update(float dt);
		void draw(Vector2 basePos = Vector2{0, 0});

		bool isSelectable() const; 
		bool isClicked(); 
		
		void setCallBack(CallBack callback);
		void triggerCallBack();

		void setText(const std::string text);
		void setTextSize(int size);
		void setTextAlignment(TextAlignMent alignment);

		void setBackGroundColor(Color color); 
		void setHoverColor(Color color);
		void setContentColor(Color color);

		void UpdateMouseCursor(); 

	private:
		Vector2 getTextPos();
		void drawText();
	protected:
		TextAlignMent alignment{TextAlignMent::Left};

		std::vector<CallBack> callBack;

		Color mHover{ ColorSetting::GetInstance().get(ColorThemeID::BUTTON_HOVER)};
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::BUTTON_BACKGROUND)};
		Color mContentColor{ ColorSetting::GetInstance().get(ColorThemeID::TEXT) };

		std::string mText{""};
		int textSize{ 32 }; 

		bool isHover{ false };
		
	};
}

