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
	this->mColor[ColorThemeID::SCREEN_BACKGROUND] = { 254, 252, 243, 255 };

	this->mColor[ColorThemeID::BUTTON_BACKGROUND] = { 219, 163, 154, 255 };
	this->mColor[ColorThemeID::BUTTON_HOVER] = { 236, 205, 180, 255 };
	this->mColor[ColorThemeID::TEXT] = WHITE; 

	this->mColor[ColorThemeID::NODE_BACKGROUND] = WHITE; 
	this->mColor[ColorThemeID::NODE_LABEL] = BLACK; 
	this->mColor[ColorThemeID::NODE_OUTLINE] = BLACK;

	this->mColor[ColorThemeID::EDGE] = BLACK;
	this->mColor[ColorThemeID::HIDE_EDGE] = {224, 224, 224, 255};

	this->mColor[ColorThemeID::HIGHLIGHT] = { 253, 153, 51, 255 };
	this->mColor[ColorThemeID::CODE_HIGHLIGHT_BACKGROUND] = { 240, 219, 219, 255 };
	this->mColor[ColorThemeID::CODE_HIGHLIGHT_HOVER] = BLACK;

	this->mColor[ColorThemeID::END_OF_WORD] = { 0, 204, 204, 255 };
	
	this->mColor[ColorThemeID::ERROR] = RED; 

	this->mColor[ColorThemeID::NAVBAR_UNSELECT] = { 190, 190, 190, 255 };
	this->mColor[ColorThemeID::NAVBAR_SELECT] = WHITE;
}

void ColorSetting::loadDarkMode()
{
	this->mColor[ColorThemeID::SCREEN_BACKGROUND] = Color{ 44, 54, 57, 255 }; 
	this->mColor[ColorThemeID::BUTTON_BACKGROUND] = Color{ 162, 123, 93, 255 }; 
	this->mColor[ColorThemeID::BUTTON_HOVER] = BLACK; 
	this->mColor[ColorThemeID::TEXT] = WHITE;

	this->mColor[ColorThemeID::NODE_BACKGROUND] = Color{ 44, 54, 57, 255 };
	this->mColor[ColorThemeID::NODE_LABEL] = WHITE; 
	this->mColor[ColorThemeID::NODE_OUTLINE] = WHITE;

	this->mColor[ColorThemeID::EDGE] = WHITE;
	this->mColor[ColorThemeID::HIDE_EDGE] = { 32, 32, 32, 255 };

	this->mColor[ColorThemeID::HIGHLIGHT] = { 112, 146, 190, 255 };
	this->mColor[ColorThemeID::CODE_HIGHLIGHT_BACKGROUND] = { 63, 78, 79, 255 };
	this->mColor[ColorThemeID::CODE_HIGHLIGHT_HOVER] = BLACK;

	this->mColor[ColorThemeID::END_OF_WORD] = { 0, 204, 204, 255 };

	this->mColor[ColorThemeID::ERROR] = { 255, 127, 39, 255 };
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
