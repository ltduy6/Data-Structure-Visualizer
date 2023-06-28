#include "OptionInputField.h"

GUI::OptionInputField::OptionInputField() : ActionsContainer()
{
	GUI::Button::Ptr mSubmit(new GUI::Button()); 
	GUI::InputBox::Ptr mFieldInput(new GUI::InputBox()); 

	mSubmit->setText("Go");
	mSubmit->setSize(Vector2{ 100, 50 });
	mFieldInput->setSize(Vector2{ 100, 50 });

	pack(mFieldInput); 
	pack(mSubmit);
}

GUI::OptionInputField::~OptionInputField()
{
}

