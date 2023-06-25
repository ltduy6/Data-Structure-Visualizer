#pragma once

#include "Component.h"

#include <functional>
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
		Button(const std::string content); 
		~Button(); 

		virtual void update(float dt);
		void draw(Vector2 basePos = Vector2{0, 0});

		bool isSelectable() const; 
		bool isClicked(); 

		void setSize(Vector2 size); 
		Vector2 GetSize(); 
		
		void setCallBack(CallBack callback);
		void triggerCallBack();

		void setText(const std::string text);
		void setTextSize(int size);
		void setTextAlignment(TextAlignMent alignment);


	private:
		Vector2 getTextPos();
		void drawText();
	protected:
		TextAlignMent alignment{TextAlignMent::Left};

		CallBack callBack;
		
		Rectangle mRect{ Rectangle{0, 0, 0, 0} };

		Color mHover{ GRAY };
		Color mColor{ 64, 64, 64, 255 };
		Color mContentColor{ WHITE }; 

		std::string mText{""};
		int textSize{ 32 }; 

		bool isHover{ false };
		
	};
}

