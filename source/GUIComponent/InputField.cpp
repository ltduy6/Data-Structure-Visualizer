#include "InputField.h"

GUI::InputField::InputField()
{
}

GUI::InputField::~InputField()
{
}

void GUI::InputField::update(float dt)
{
	if (this->GetActive())
	{
		this->UpdateMouseCursor();
	}
	this->updateField(dt);
}

void GUI::InputField::draw(Vector2 base)
{
	this->mRect.x = base.x + this->mPos.x; 
	this->mRect.y = base.y + this->mPos.y; 

	Vector2 boundLabel = MeasureTextEx(font, label.c_str(), this->FontSize, 0); 
	Vector2 pos = { this->mRect.x, this->mRect.y + this->mRect.height / 2 - boundLabel.y / 2 }; 

	if (label != "")
	{
		DrawTextEx(this->font, this->label.c_str(), pos, this->FontSize, 0, this->mLabelColor);

		this->setSizeBox(Vector2{ this->mRect.width - boundLabel.x - 15 * Helper::scaleFactorX(), this->mRect.height - 5 * Helper::scaleFactorY()});
		drawField(Vector2{ this->mRect.x + 5 * Helper::scaleFactorX() + boundLabel.x, this->mRect.y + 2 * Helper::scaleFactorY()});
	}
	else {
		this->setSizeBox(Vector2{ this->mRect.width, this->mRect.height});
		drawField(this->mPos);
	}
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
