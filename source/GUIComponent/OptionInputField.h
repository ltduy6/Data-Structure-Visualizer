#pragma once
#include "ActionsContainer.h"
#include "InputBox.h"
#include "Button.h"
#include <map>

namespace GUI {
	class OptionInputField : public ActionsContainer
	{
	public:
		typedef std::shared_ptr<OptionInputField> Ptr; 
	public:
		OptionInputField(); 
		~OptionInputField();
		void AddInputField(Vector2 size, std::string label); 
		void AddActionSubmit(std::function<void()> action); 
		void AddActionRandom(std::function<void()> action);
		void DrawError(); 
		void DrawInput(); 
		int checkValidSubmit(); 
		std::vector<int> ExtractValue(); 
	private:
		GUI::Button::Ptr mSubmit; 
		GUI::Button::Ptr mRandom; 
		GUI::InputBox::Ptr mInputField; 
		std::vector<std::string> Errors; 
		std::string error{""};
	};
}

