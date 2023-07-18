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
		static constexpr float ANIMATION_TIME = 0.6f;
		static constexpr float FACTORS[] = { 0.25f, 0.5f, 1.0f, 2.0f }; 
	public:
		ControlScene(std::vector<VisualScene>& container, VisualScene& displayScene); 
		~ControlScene(); 

		void update(float dt); 
		void draw(); 
		void reset(); 
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

	private:
		std::vector<VisualScene>* mContainer; 
		VisualScene* mDisplayScene; 

		int currentIndScene{ 0 }; 
		int currentIndSpeed{ 2 };

		Action mActionStatus{ Action::None }; 
		bool isPaused{ false };

		float mTime{ 0 };

		GUI::ActionsContainer mButtonContainer; 


	};
}


