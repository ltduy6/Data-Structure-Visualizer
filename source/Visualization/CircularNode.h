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

		void SetValue(int value);
		int GetValue() const;

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
	private:
		float mRadius{ ELEMENT_SIZE / 2 };
		int mValue{ 0 };
		std::string mLabel{ "" };

		Color mValueColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND) };
		Color mOutlineColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE) };
		Color mLabelColor{ ColorSetting::GetInstance().get(ColorThemeID::ERROR) };

		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
	};
}

