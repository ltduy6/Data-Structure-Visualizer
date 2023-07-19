#pragma once

#include "raylib.h"
#include "../Helper/ColorSetting.h"

#include <string> 
#include <vector>

namespace Visualize {
	class CodeHighLight
	{
	public:
		CodeHighLight();

		void draw();

		void reset();
		void addCode(std::string code);

		void highlightCode(std::vector<int> lines);
		void setTracker(int tracker);
	private:
		std::vector<std::pair<std::string, bool>> mCode;
		std::vector<std::vector<int>> mIndex;

		int mTracker{ 0 };

		Rectangle mRect = { 0, 0, 0, 0 };
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::CODE_HIGHLIGHT_BACKGROUND) };
		Color mText{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };
		Color mTextHighLight{ ColorSetting::GetInstance().get(ColorThemeID::TEXT) };
	};
}

