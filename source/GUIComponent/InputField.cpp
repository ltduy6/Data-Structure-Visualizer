#include "InputField.h"

GUI::InputField::InputField() : mRandom(new GUI::Button())
{
	this->mRandom->SetSize(Vector2{ Constant::BUTTON_WIDTH - 40, Constant::BUTTON_HEIGHT }); 
	this->mRandom->setText("Random"); 
	this->mRandom->setTextAlignment(GUI::Button::TextAlignMent::Center); 
	this->mRandom->setCallBack([this]() {
		this->Random();
		});
}

GUI::InputField::~InputField()
{
}

void GUI::InputField::update(float dt)
{
	if (this->GetActive())
	{
		this->UpdateMouseCursor();
		this->mRandom->update(dt);
	}
	this->updateField(dt);
}

void GUI::InputField::draw(Vector2 base)
{
	this->mRect.x = base.x + this->mPos.x; 
	this->mRect.y = base.y + this->mPos.y; 

	Vector2 boundLabel = MeasureTextEx(font, label.c_str(), this->FontSize, 0); 
	Vector2 pos = { this->mRect.x, this->mRect.y + this->mRect.height / 2 - boundLabel.y / 2 }; 

	DrawTextEx(this->font, this->label.c_str(), pos, this->FontSize, 0, this->mLabelColor); 

	this->mRandom->draw(Vector2{ this->mRect.x + this->mRect.width - this->mRandom->GetSize().x - 5, this->mRect.y});

	this->setSizeBox(Vector2{ this->mRect.width - boundLabel.x - 15 - this->mRandom->GetSize().x, this->mRect.height - 5});
	drawField(Vector2{ this->mRect.x + 5 + boundLabel.x, this->mRect.y + 2 });
}

void GUI::InputField::SetLabel(const std::string label)
{
	this->label = label;
}

std::string GUI::InputField::GetLabel() const
{
	return this->label;
}

void GUI::InputField::UpdateMouseCursor()
{
	Vector2 pos = GetMousePosition();
	if (CheckCollisionPointRec(pos, this->mRect))
		SetMouseCursor(MOUSE_CURSOR_IBEAM);
}
