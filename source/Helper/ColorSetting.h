#pragma once

#include "raylib.h"
#include <map>
#include <memory>
#include <assert.h>

enum class ColorThemeID
{
	SCREEN_BACKGROUND,
	BUTTON_BACKGROUND, 
	BUTTON_HOVER,
	TEXT,
	NODE_BACKGROUND,
	NODE_OUTLINE, 
	NODE_LABEL,
	EDGE,
	ERROR
};

class ColorSetting
{
public:
	ColorSetting();
	~ColorSetting();
	static ColorSetting& GetInstance();
	Color get(ColorThemeID id);
	void loadLightMode();
	void loadDarkMode();
	void load();
	void SwitchTheme();
private:
	int currentTheme{0};
	std::map<ColorThemeID, Color> mColor; 
};

