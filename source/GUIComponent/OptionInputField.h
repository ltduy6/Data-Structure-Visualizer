#pragma once
#include "Container.h"
#include "InputBox.h"
#include "Button.h"
#include <map>

namespace GUI {
	class OptionInputField : public Container
	{
	public:
		typedef std::shared_ptr<OptionInputField> Ptr; 
	public:
		OptionInputField(); 
		~OptionInputField();
		void SetOption(std::string content, std::vector<GUI::InputBox::Ptr> fields,
			std::function<void(std::map<std::string, std::string>)> CallBack); 
		void SetNoFieldOption(std::string content, std::function<void()> CallBack);
		void drawCurrent(Vector2 base);
	private:
		std::map<std::string, std::string> ExtractInput(); 
		void AddInput(InputBox::Ptr InputBox); 
		void AddSubmit(std::function<void(std::map<std::string, std::string>)> CallBack); 
	private:
		std::map<std::string, std::string> InputData;
	};
}

