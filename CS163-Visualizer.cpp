#include <iostream>
#include "source/GUIComponent/Button.h"
#include "source/GUIComponent/InputBox.h"
#include "source/GUIComponent/ActionsContainer.h"
#include "source/GUIComponent/ActionsList.h"
#include "source/ResourceHolder/FontHolder.h"
#include "source/Helper/ColorSetting.h"
#include "source/GUIComponent/OptionInputField.h"
#include "source/Helper/GlobalVar.h"

int main()
{
	InitWindow(Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT, "VisualALGO");
	SetTargetFPS(60);

	FontHolder::getInstance().load(FontID::Roboto, "assets/Fonts/Roboto-Medium.ttf");

	ColorSetting::GetInstance().load(); 

	GUI::ActionsList actionlist; 

	for (int i = 0; i < 3; ++i)
	{
		GUI::ActionsContainer::Ptr container(new GUI::ActionsContainer());
		GUI::Button::Ptr button(new GUI::Button());
		button->setText("Hello");
		button->setTextAlignment(GUI::Button::TextAlignMent::Center);

		GUI::InputBox::Ptr InputBox(new GUI::InputBox());
		InputBox->SetSize(Vector2{ 300, 50 });
		InputBox->SetLabel("v =");

		GUI::InputBox::Ptr InputBox_1(new GUI::InputBox());
		InputBox_1->SetSize(Vector2{ 300, 50 });
		InputBox_1->SetLabel("i =");

		std::vector<GUI::InputBox::Ptr> fields;
		fields.push_back(InputBox);
		fields.push_back(InputBox_1);

		GUI::OptionInputField::Ptr optionInputField(new GUI::OptionInputField());
		optionInputField->SetOption("User define", fields, [&](std::map<std::string, std::string> inputs) {
			std::cout << inputs["v ="] << '\n';
			std::cout << inputs["i ="] << '\n';
			actionlist.hideAllOptions();
			});

		container->pack(optionInputField);

		actionlist.AddOperation(button, container);
	}

	while (WindowShouldClose() == false)
	{
		BeginDrawing();
		ClearBackground(WHITE);
		actionlist.update(GetFrameTime());
		actionlist.draw(Vector2{ 100, 100 });
		EndDrawing();
	}

	CloseWindow(); 
	return 0;
}

