#include <iostream>
#include "source/GUIComponent/Button.h"
#include "source/ResourceHolder/FontHolder.h"
#include "source/GlobalVar.h"

int main()
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO");
	SetTargetFPS(60);

	FontHolder::getInstance().load(FontID::Roboto, "assets/Fonts/Roboto-Medium.ttf");

	GUI::Button* button = new GUI::Button({ 12, 12, 200, 250 });
	button->setText("Hello");
	button->setTextSize(30);
	while (WindowShouldClose() == false)
	{
		button->update(GetFrameTime());
		BeginDrawing();
		ClearBackground(WHITE); 
		button->draw();
		EndDrawing();
	}

	delete button; 
	CloseWindow(); 
	return 0;
}

