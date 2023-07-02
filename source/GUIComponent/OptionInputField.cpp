#include "OptionInputField.h"
#include "../Helper/GlobalVar.h"

GUI::OptionInputField::OptionInputField() : Container(), mInputField(new GUI::Container())
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
	this->mInputField->unPackAll(); 
	this->mInputField->SetActive(false); 

	auto actionOnSubmit = [CallBack, this]() {CallBack(this->InputData); };

	if (fields.empty())
	{
		GUI::Button::Ptr newButton(genButton(content, actionOnSubmit));
		newButton->SetSize(Vector2{ Constant::BUTTON_WIDTH, Constant::BUTTON_HEIGHT });
		pack(newButton); 
		return; 
	}
	
	auto actionToggle = [this]() {this->mInputField->ToggleActive(); };

	GUI::Button::Ptr button(genButton(content, actionToggle));  
	button->SetActive(true);
	pack(button); 

	for (auto& field : fields)
		AddInput(field); 

	AddSubmit(CallBack);
	button->SetSize(this->GetSize());
	pack(this->mInputField);
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

Vector2 GUI::OptionInputField::GetSize() const
{
	float width = 0; 
	float height = 0; 

	for (auto field : this->mInputField->getChildren())
	{
		width += field->GetSize().x; 
		height = std::max(height, field->GetSize().y); 
	}

	return Vector2{ width + 5, height};
}


std::map<std::string, std::string> GUI::OptionInputField::ExtractInput()
{
	std::map<std::string, std::string> inputs; 
	auto range = this->mInputField.get()->getChildren(); 
	for (auto it = range.begin(); it + 1 != range.end(); ++it) {
		InputBox* input = dynamic_cast<InputBox*>(it->get());
		inputs[input->GetLabel()] = input->getInputText(); 
	}
	return inputs;
}

void GUI::OptionInputField::AddInput(InputBox::Ptr InputBox)
{
	Vector2 lastInputPos = this->mChildren.begin()->get()->GetPos(); 
	lastInputPos.y += Constant::BUTTON_HEIGHT + 5;
	if (!this->mInputField.get()->getChildren().empty())
	{
		Vector2 lastPos = this->mInputField.get()->getChildren().rbegin()->get()->GetPos(); 
		Vector2 size = this->mInputField.get()->getChildren().rbegin()->get()->GetSize(); 

		lastInputPos.x = lastPos.x + size.x; 
	}
	InputBox->SetPos(lastInputPos); 
	this->mInputField->pack(InputBox);
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
	Vector2 lastChildPos = this->mInputField.get()->getChildren().rbegin()->get()->GetPos();
	Vector2 lastChildSize = this->mInputField.get()->getChildren().rbegin()->get()->GetSize(); 

	buttonSubmit->SetSize(Vector2{ 50, lastChildSize.y }); 
	buttonSubmit->SetPos(Vector2{ lastChildPos.x + lastChildSize.x + 3, 
								lastChildPos.y + (lastChildSize.y - buttonSubmit->GetSize().y) / 2});
	this->mInputField->pack(buttonSubmit);
}



