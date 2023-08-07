#pragma once

#include "raylib.h"
#include "../Helper/ColorSetting.h"
#include "../Helper/GlobalVar.h"
#include "../ResourceHolder/FontHolder.h"
#include "../Helper/Helper.h"

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

		Rectangle mRect = { (Constant::WINDOW_WIDTH - 900 - 5) * Helper::scaleFactorX(), (Constant::WINDOW_HEIGHT - 3 * Constant::BUTTON_HEIGHT) * Helper::scaleFactorY(), 900 * Helper::scaleFactorX(), Constant::BUTTON_HEIGHT * Helper::scaleFactorY()};
		 
		Color mColor{ ColorSetting::GetInstance().get(ColorThemeID::CODE_HIGHLIGHT_BACKGROUND) };
		Color mTextColor{ ColorSetting::GetInstance().get(ColorThemeID::NODE_LABEL) };

		Font font{ FontHolder::getInstance().get(FontID::Courier) };
	};
}

