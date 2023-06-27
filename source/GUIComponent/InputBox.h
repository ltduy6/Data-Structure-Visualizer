#pragma once
#include "Component.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/Helper.h"
#include "raylib.h"

#include <memory>
#include <vector>
#include <string>
#include <assert.h>
#include <functional>

namespace GUI {
	class InputBox : public Component
	{
	public:
		typedef std::shared_ptr<InputBox> Ptr;
	public:
		InputBox();
		~InputBox();
		void draw(Vector2 base);
		bool isSelectable() const;
		void update(float dt);
		void setSize(Vector2 base);
		std::string getInputText() const;
		void resetLabel(); 
	public:
		static std::function<bool(std::string)> integerValid(int minValue, int maxValue);
		static std::function<bool(std::string)> integerSpaceSeparatedListValid();
	private:
		void checkInteraction();
		void drawCursor(Vector2 base); 
		int ind_start{ 0 };
		int ind_end{ 0 };
		int ind_mouse{ 0 };
	private:
		Vector2 mFieldSize{ Vector2{0, 0} };
		std::string mInputText;
		Color mTextColor{ BLACK }; 
		Color mColor{WHITE};
		Color mBorderColor{ BLACK };
		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
		Rectangle mRect{ Rectangle {0, 0, 0, 0} };
		Rectangle mCursor{ Rectangle{0, 0, 0, 0} }; 
		float fontSize{ 30 };
		float mBorderThickness{ 1 };
		float countTime{ 0 };
		bool mIsFocused{ false };
		bool mCursorVisible{ false };
	};
}

