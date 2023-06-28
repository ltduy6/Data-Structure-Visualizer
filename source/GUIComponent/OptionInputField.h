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
	};
}

