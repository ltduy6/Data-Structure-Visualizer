#include "ColorSetting.h"

ColorSetting::ColorSetting()
{
}

ColorSetting::~ColorSetting()
{
}

ColorSetting& ColorSetting::GetInstance()
{
	// TODO: insert return statement here
	static ColorSetting instance; 
	return instance;
}

Color ColorSetting::get(ColorThemeID id)
{
	// TODO: insert return statement here
	auto found = this->mColor.find(id); 
	assert(found != this->mColor.end()); 

	return found->second; 
}

void ColorSetting::loadLightMode()
{
	this->mColor[ColorThemeID::SCREEN_BACKGROUND] = WHITE; 
	this->mColor[ColorThemeID::BUTTON_BACKGROUND] = Color{ 64, 64, 64, 255 };
	this->mColor[ColorThemeID::BUTTON_HOVER] = GRAY; 
	this->mColor[ColorThemeID::TEXT] = WHITE; 
	this->mColor[ColorThemeID::NODE_BACKGROUND] = WHITE; 
	this->mColor[ColorThemeID::NODE_LABEL] = BLACK; 
	this->mColor[ColorThemeID::NODE_OUTLINE] = BLACK;
}

void ColorSetting::loadDarkMode()
{
	this->mColor[ColorThemeID::SCREEN_BACKGROUND] = Color{ 44, 54, 57, 255 }; 
	this->mColor[ColorThemeID::BUTTON_BACKGROUND] = Color{ 162, 123, 93, 255 }; 
	this->mColor[ColorThemeID::BUTTON_HOVER] = BLACK; 
	this->mColor[ColorThemeID::TEXT] = WHITE;
}

void ColorSetting::load()
{
	this->currentTheme = 0;
	this->loadLightMode(); 
}

void ColorSetting::SwitchTheme()
{
	this->currentTheme = 1 - this->currentTheme; 
	switch (this->currentTheme)
	{
	case 0:
		this->loadLightMode(); 
		break;
	case 1:
		this->loadDarkMode(); 
		break;
	default:
		break; 
	}
}
