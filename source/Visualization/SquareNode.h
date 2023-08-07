#pragma once
#include "SceneNode.h"
#include "../Helper/ColorSetting.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/Helper.h"
#include <string>
#include <set>

namespace Visualize {
	class SquareNode : public SceneNode
	{
	public:
		SquareNode();
		~SquareNode();
		void draw();

		void SetValue(int value);
		std::multiset<int> GetValue() const;

		void EraseValue(int value); 
		void ClearValue();

		void SetLabel(std::string label);
		std::string GetLabel() const;

		bool hasValue() const; 

		void SetValueColor(Color color);
		void SetColor(Color color);
		void SetOutlineColor(Color color);

		Color GetOutlineColor() const;
		Color GetValueColor() const;
		Color GetColor() const;

		Vector2 GetPosIndex(int index) const;
		Vector2 GetPosMid() const;

		void resetColor();
		int getObjectId() const;
	private:
		Vector2 mSize = { 100 * Helper::scaleFactorX(), 60 * Helper::scaleFactorY()};
		std::multiset<int> mSetValue;
		std::string mLabel{ "" };
		std::string formatValue{ "000" };
		
		Color mValueColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_BACKGROUND) };
		Color mOutlineColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_OUTLINE) };
		Color mLabelColor{ ColorSetting::GetInstance().get(ColorThemeID::ERROR) };

		Font font{ FontHolder::getInstance().get(FontID::Roboto) };
	};
}

