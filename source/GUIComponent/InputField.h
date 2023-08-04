#pragma once
#include "Component.h"
#include "Button.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/GlobalVar.h"

namespace GUI
{
	class InputField : public Component
	{
	public:
		InputField(); 
		~InputField(); 
		virtual void update(float dt); 
		virtual void draw(Vector2 base = Vector2{ 0, 0 });
		virtual void drawField(Vector2 base) = 0;
		virtual void updateField(float dt) = 0; 
		virtual void setSizeBox(Vector2 base) = 0;
		virtual void Random() = 0;
		void SetLabel(const std::string label);
		std::string GetLabel() const; 
		void UpdateMouseCursor();
	private:
		std::string label{ "" };
		Color mLabelColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL)};
		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
		float FontSize{ 36 };
	};
}

