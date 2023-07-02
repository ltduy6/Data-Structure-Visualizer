#pragma once
#include "InputField.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/Helper.h"
#include "raylib.h"

#include <memory>
#include <vector>
#include <string>
#include <assert.h>
#include <functional>

namespace GUI {
	class InputBox : public InputField
	{
	public:
		typedef std::shared_ptr<InputBox> Ptr;
	public:
		explicit InputBox();
		~InputBox();
		virtual void drawField(Vector2 base);
		virtual void updateField(float dt);
		virtual void setSizeBox(Vector2 base);
		virtual std::string getInputText() const;

		bool IntegerValidator(int number) const; 
		bool IntegerSpaceValidator() const; 

		void resetLabel(); 

	private:
		void checkInteraction();
		void drawCursor(Vector2 base); 
		virtual void Random(); 
	private:
		int ind_start{ 0 };
		int ind_end{ 0 };
		int ind_mouse{ 0 };
		int minValue{0}; 
		int maxValue{100};
	private:
		std::string mInputText;
		Color mTextColor{ BLACK }; 
		Color mColor{WHITE};
		Color mBorderColor{ BLACK };
		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
		Rectangle mBound{ Rectangle{0, 0, 0, 0} };
		Rectangle mCursor{ Rectangle{0, 0, 0, 0} }; 
		float fontSize{ 30 };
		float mBorderThickness{ 1 };
		float countTime{ 0 };
		bool mIsFocused{ false };
		bool mCursorVisible{ false };
	};
}

