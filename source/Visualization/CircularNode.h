#pragma once
#include "SceneNode.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"

namespace Visualize {
	class CircularNode : public SceneNode
	{
	public:
		CircularNode();
		~CircularNode();
		virtual void draw();
		virtual void update(float dt);

		void SetValue(int value);
		int GetValue() const;

		void SetCharValue(std::string value);
		std::string GetCharValue() const;

		void SetType(bool isNum);
		bool GetType() const;

		void SetLabel(std::string label); 
		std::string GetLabel() const; 

		void SetValueColor(Color color);
		void SetColor(Color color);
		void SetOutlineColor(Color color);

		Color GetOutlineColor() const; 
		Color GetValueColor() const; 
		Color GetColor() const; 

		void resetColor(); 
		int getObjectId() const; 

		bool isMouseHover(); 
	private:
		float mRadius{ ELEMENT_SIZE / 2 };
		int mValue{ 0 };
		bool isNumber{ true };

		std::string mLabel{ "" };
		std::string mCharValue{ "" };

		Color mValueColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND) };
		Color mOutlineColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE) };
		Color mLabelColor{ ColorSetting::GetInstance().get(ColorThemeID::ERROR) };

		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
		Font fontLabel{ FontHolder::getInstance().get(FontID::Roboto_Bold) };
	};
}

