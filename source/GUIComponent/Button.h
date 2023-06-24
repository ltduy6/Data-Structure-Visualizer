#pragma once

#include "Component.h"

#include <functional>
#include <string>

namespace GUI {
	class Button : public Component
	{
	public: 
		typedef std::shared_ptr<Button> Ptr;
		typedef std::function<Color(Color)> Filter;
		typedef std::function<void()> CallBack;

		enum class ButtonState {
			None, 
			Focused, 
			Active
		};

	public:
		Button(Rectangle bound); 
		~Button(); 

		void update(float dt); 
		void draw(); 

		void setSize(Vector2 size); 
		
		void setCallBack(CallBack callback);
		void triggerCallBack();

		void setText(const std::string text);
		void setTextSize(int size);

		Color getColor() const;

		void activate(); 
		void deactivate();
	private:
		void checkInteraction();
	protected:
		ButtonState mState{ ButtonState::None };

		CallBack callBack;
		
		Rectangle mRect;

		Color mHover{ 64, 64, 64, 255 };
		Color mContentColor{ WHITE }; 

		std::string mText{""};
		int textSize{ 0 }; 

		bool mIsActivated{ true }; 
		Filter mInactivatedFilter;
		
	};
}

