#include <iostream>
#include "source/GUIComponent/Button.h"
#include "source/GUIComponent/ActionsContainer.h"
#include "source/GUIComponent/ActionsList.h"
#include "source/ResourceHolder/FontHolder.h"
#include "source/GlobalVar.h"

int main()
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO");
	SetTargetFPS(60);

	FontHolder::getInstance().load(FontID::Roboto, "assets/Fonts/Roboto-Medium.ttf");

	GUI::ActionsList actionList;

	std::vector<std::string> a = { "Insert", "Update", "Search" }; 

	for (int i = 0; i < a.size(); ++i)
	{
		GUI::Button::Ptr button(new GUI::Button(a[i]));
		button->setTextAlignment(GUI::Button::TextAlignMent::Left);
		button->setSize(Vector2{ 100, 100 });

		GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer()); 
		GUI::Button::Ptr button_1(new GUI::Button("Hello")); 
		GUI::Button::Ptr button_2(new GUI::Button("Bye"));
		button_1->setSize(Vector2{ 100, 50 }); 
		button_2->setSize(Vector2{ 100, 50 });
		container->pack(button_1); 
		container->pack(button_2);


		actionList.AddOperation(button, container); 
	}


	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(WHITE); 
		actionList.update(GetFrameTime());
		actionList.draw({ 100, 100 });
		EndDrawing();
	}

	CloseWindow(); 
	return 0;
}

