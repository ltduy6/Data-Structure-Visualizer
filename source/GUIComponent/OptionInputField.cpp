#include "OptionInputField.h"
#include <iostream>
#include <sstream>

GUI::OptionInputField::OptionInputField() : ActionsContainer()
{
	this->mInputField = std::make_shared<GUI::InputBox>();
	this->Errors = { "Please fill in a number or space-separated array of numbers!", "Sorry, only values between -99 and 99 can be inserted."};

	this->mSubmit = std::make_shared<GUI::Button>(); 
	this->mSubmit->setText("Go");
	this->mSubmit->setSize(Vector2 {50, 50});
	this->mSubmit->setTextAlignment(GUI::Button::TextAlignMent::Center); 
	this->mSubmit->setCallBack([this]() {
		DrawInput();
		std::cout << checkValidSubmit() << '\n';
		if (this->checkValidSubmit() >= 0)
			this->error = this->Errors[this->checkValidSubmit()];
		});

	this->mRandom = std::make_shared<GUI::Button>(); 
	this->mRandom->setText("Random"); 
	this->mRandom->setSize(Vector2{ 120, 50 });
	this->mRandom->setTextAlignment(GUI::Button::TextAlignMent::Center);

	pack(this->mInputField); 
	pack(this->mRandom);
	pack(this->mSubmit);
}

GUI::OptionInputField::~OptionInputField()
{
}

void GUI::OptionInputField::AddInputField(Vector2 size, std::string label)
{
	this->mInputField->setSize(size);
}

void GUI::OptionInputField::AddActionSubmit(std::function<void()> action)
{
	this->mSubmit->setCallBack(action); 
}

void GUI::OptionInputField::AddActionRandom(std::function<void()> action)
{
	this->mRandom->setCallBack(action);
}

void GUI::OptionInputField::DrawError()
{
	Font font = FontHolder::getInstance().get(FontID::Roboto); 
	Vector2 pos = { this->mPos.x + this->GetSize().x + 50, this->mPos.y + this->GetSize().y / 2 - 12 };

	DrawTextEx(font, this->error.c_str(), pos, 24, 0, BLACK);
}

void GUI::OptionInputField::DrawInput()
{
	std::cout << this->mInputField->getInputText() << '\n';
}


int GUI::OptionInputField::checkValidSubmit()
{
	if (this->mInputField->IntegerSpaceValidator() == false)
	{
		return 0; 
	}
	else {
		std::stringstream ss(this->mInputField->getInputText()); 
		int number = 0; 
		while (ss >> number)
			if (this->mInputField->IntegerValidator(number) == false)
			{
				return 1;
			}
		return -1; 
	}
}

std::vector<int> GUI::OptionInputField::ExtractValue()
{
	std::vector<int> values;
	std::stringstream ss(this->mInputField->getInputText()); 
	int number = 0; 
	while (ss >> number)
	{
		values.push_back(number);
	}
	return values; 
}



