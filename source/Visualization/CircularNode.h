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

		void SetValueColor(Color color);
		void SetColor(Color color);
		void SetOutlineColor(Color color);

		Color GetOutlineColor() const; 
		Color GetValueColor() const; 
		Color GetColor() const; 

		void resetColor(); 
	private:
		float mRadius{ 30 };
		int mValue{ 0 };

		Color mValueColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND) };
		Color mOutlineColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE) };

		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
	};
}

