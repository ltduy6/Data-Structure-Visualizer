#pragma once

#include "../Helper/ColorSetting.h"
#include "../Helper/GlobalVar.h"
#include "../GUIComponent/Button.h"
#include "../GUIComponent/ActionsContainer.h"
#include "VisualScene.h"

#include <vector>

namespace Visualize {
	class ControlScene
	{
	public:
		static constexpr float ANIMATION_TIME = 0.8f;
		static constexpr float FACTORS[] = { 0.25f, 0.5f, 0.75f, 1.0f, 1.25f, 1.5f, 1.75f, 2.0f }; 
		static constexpr int FACTORS_SIZE = 8;
		std::vector<std::string> FACTORS_STRING = {"0.25x", "0.5x", "0.75x", "1.0x", "1.25x", "1.5x", "1.75x", "2.0x"};
	public:
		ControlScene(std::vector<VisualScene>& container, VisualScene& displayScene); 
		~ControlScene(); 

		void update(float dt); 
		void draw(); 
		void reset(); 

		bool getHoverStatus() const;
		int getCurrentIndex() const; 
	private:
		enum class Action {
			None, 
			Prev,
			Next
		};
	private:
		void updateDisplayingScene(float dt); 
		void updateSpeedModifier(float dt); 

		void nextScene(); 
		void resetScene(); 
		void prevScene(); 
		void forwardScene(); 

		void togglePause();
		void setPause(bool isPause); 
		void loadButton(GUI::Button::Ptr& button, std::string title); 
		void drawSpeed();

	private:
		std::vector<VisualScene>* mContainer; 
		VisualScene* mDisplayScene; 

		int currentIndScene{ 0 }; 
		int currentIndSpeed{ 3 };

		bool isPaused{ false };
		bool isHover{ false };
		float mTime{ 0 };


		Action mActionStatus{ Action::None }; 
		GUI::ActionsContainer mButtonContainer;
		GUI::Button buttonSpeedUp; 
		GUI::Button buttonSpeedDown;
	};
}


