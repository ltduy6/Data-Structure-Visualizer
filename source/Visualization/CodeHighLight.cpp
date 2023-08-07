#include "CodeHighLight.h"
#include <iostream>

Visualize::CodeHighLight::CodeHighLight()
{
	this->mIndex.push_back({}); 
}

void Visualize::CodeHighLight::draw()
{
	for (auto index : this->mIndex[this->mTracker])
		this->mCode[index].second = true; 
	float textSize = this->mRect.height * 2 / 3;
	int textAlignment = 10 * Helper::scaleFactorX(); 
	int numCode = this->mCode.size(); 
	for (int i = numCode - 1 ; i >= 0 ; --i)
	{
		if (this->mCode[i].second)
		{
			this->mColor = ColorSetting::GetInstance().get(ColorThemeID::CODE_HIGHLIGHT_HOVER);
			this->mTextColor = ColorSetting::GetInstance().get(ColorThemeID::TEXT);
		}
		else {
			this->mColor = ColorSetting::GetInstance().get(ColorThemeID::CODE_HIGHLIGHT_BACKGROUND);
			this->mTextColor = ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL); 
		}
		DrawRectangleRec(Rectangle{ this->mRect.x, this->mRect.y - (numCode - 1 - i) * this->mRect.height, this->mRect.width, this->mRect.height }, this->mColor); 
		DrawTextEx(font, this->mCode[i].first.c_str(),
			{ this->mRect.x + textAlignment, this->mRect.y - (numCode - 1 - i) * this->mRect.height + this->mRect.height / 2 - textSize / 2 },
			textSize, 0, this->mTextColor);
		mCode[i].second = false; 
	}
}

void Visualize::CodeHighLight::reset()
{
	this->mCode.clear(); 
	this->mIndex.clear(); 
	this->mIndex.push_back({}); 
	this->mTracker = 0; 
}

void Visualize::CodeHighLight::addCode(std::string code)
{
	this->mCode.push_back(std::make_pair(code, false));
}

void Visualize::CodeHighLight::highlightCode(std::vector<int> lines)
{
	this->mIndex.push_back(lines); 
}

void Visualize::CodeHighLight::setTracker(int tracker)
{
	this->mTracker = tracker; 
	assert(this->mTracker >= 0 && this->mTracker < this->mIndex.size()); 
}
