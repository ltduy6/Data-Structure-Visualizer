#include "OptionInputField.h"
#include "../Helper/GlobalVar.h"

GUI::OptionInputField::OptionInputField() : Container()
{
	
}

GUI::OptionInputField::~OptionInputField()
{
}

void GUI::OptionInputField::SetOption(std::string content, std::vector<GUI::InputBox::Ptr> fields, 
	std::function<void(std::map<std::string, std::string>)> CallBack)
{
	auto genButton = [&, this](std::string content, std::function<void()> action) -> GUI::Button::Ptr {
		GUI::Button::Ptr button(new GUI::Button()); 
		button->setText(content); 
		button->setTextAlignment(GUI::Button::TextAlignMent::Center);
		button->setCallBack(action); 
		return button; 
	};

	this->unPackAll(); 

	auto actionOnSubmit = [CallBack, this]() {CallBack(this->InputData); };

	if (fields.empty())
	{
		GUI::Button::Ptr newButton(genButton(content, actionOnSubmit));
		newButton->SetSize(Vector2{ Constant::BUTTON_WIDTH * Helper::scaleFactorX(), Constant::BUTTON_HEIGHT * Helper::scaleFactorY()});
		pack(newButton); 
		return; 
	}

	for (auto& field : fields)
		AddInput(field); 

	AddSubmit(CallBack);
}

void GUI::OptionInputField::SetNoFieldOption(std::string content, std::function<void()> CallBack)
{
	SetOption(content, {}, [CallBack](std::map<std::string, std::string> input) {CallBack(); }); 
}

void GUI::OptionInputField::drawCurrent(Vector2 base)
{
	this->mRect.x = base.x + this->mPos.x; 
	this->mRect.y = base.y + this->mPos.y; 
}

std::map<std::string, std::string> GUI::OptionInputField::ExtractInput()
{
	std::map<std::string, std::string> inputs; 
	auto range = this->mChildren; 
	for (auto it = range.begin(); it + 1 != range.end(); ++it) {
		InputBox* input = dynamic_cast<InputBox*>(it->get());
		inputs[input->GetLabel()] = input->getInputText(); 
	}
	return inputs;
}

void GUI::OptionInputField::AddInput(InputBox::Ptr InputBox)
{
	Vector2 lastInputPos = this->mPos; 
	if (!this->mChildren.empty())
	{
		Vector2 lastPos = this->mChildren.rbegin()->get()->GetPos(); 
		Vector2 size = this->mChildren.rbegin()->get()->GetSize(); 

		lastInputPos.x = lastPos.x + size.x; 
	}
	InputBox->SetPos(lastInputPos); 
	pack(InputBox);
}

void GUI::OptionInputField::AddSubmit(std::function<void(std::map<std::string, std::string>)> CallBack)
{
	auto genButton = [&, this](std::string text, std::function<void()> action) -> GUI::Button::Ptr {
		GUI::Button::Ptr button(new GUI::Button()); 
		button->setText(text);
		button->setTextSize(36); 
		button->setCallBack(action); 
		button->setTextAlignment(GUI::Button::TextAlignMent::Center); 

		return button; 
	}; 

	GUI::Button::Ptr buttonSubmit(genButton("Go", [CallBack, this]() {CallBack(this->ExtractInput()); })); 
	Vector2 lastChildPos = this->mChildren.rbegin()->get()->GetPos();
	Vector2 lastChildSize = this->mChildren.rbegin()->get()->GetSize(); 

	buttonSubmit->SetSize(Vector2{ 50 * Helper::scaleFactorX(), lastChildSize.y});
	buttonSubmit->SetPos(Vector2{ lastChildPos.x + lastChildSize.x + 3, 
								lastChildPos.y + (lastChildSize.y - buttonSubmit->GetSize().y) / 2});
	pack(buttonSubmit);
}



