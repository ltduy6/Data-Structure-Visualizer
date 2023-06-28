#include <iostream>
#include "source/GUIComponent/Button.h"
#include "source/GUIComponent/InputBox.h"
#include "source/GUIComponent/ActionsContainer.h"
#include "source/GUIComponent/ActionsList.h"
#include "source/ResourceHolder/FontHolder.h"
#include "source/GUIComponent/OptionInputField.h"
#include "source/GlobalVar.h"

int main()
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO");
	SetTargetFPS(60);

	FontHolder::getInstance().load(FontID::Roboto, "assets/Fonts/Roboto-Medium.ttf");

	
	std::vector<std::string> a = { "Create", "Insert", "Delete" }; 

	GUI::ActionsList actionList;

	for (auto x : a)
	{
		GUI::Button::Ptr button(new GUI::Button()); 
		button->setText(x); 

		GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer()); 

		GUI::Button::Ptr button_2(new GUI::Button()); 
		button_2->setText("Bye"); 
		button_2->setSize(Vector2{ 150, 50 }); 

		GUI::OptionInputField::Ptr input(new GUI::OptionInputField()); 

		container->pack(button_2); 
		container->pack(input);

		actionList.AddOperation(button, container); 
	}

	

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		actionList.update(GetFrameTime());
		actionList.draw(Vector2{ 100, 100 });
		EndDrawing();
	}

	CloseWindow(); 
	return 0;
}

