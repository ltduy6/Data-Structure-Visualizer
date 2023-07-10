#pragma once
#include "State.h"
#include "../GUIComponent/ActionsList.h"
#include "../GUIComponent/ActionsContainer.h"
#include "../GUIComponent/InputBox.h"
#include "../GUIComponent/OptionInputField.h"
#include "../Helper/GlobalVar.h"
#include "../Visualization/CircularNode.h"
#include "../Visualization/VisualScene.h"
#include "../Visualization/Visualization.h"
#include "../Core/AVL.h"

class BSTState : public State
{
public:
	struct InputData {
		float width;
		std::string label;
	};
public:
	BSTState(StateStack& stack, Context context); 
	virtual void draw();
	virtual bool update(float dt); 
protected:
	GUI::ActionsList actionList;
	virtual void AddOperation(); 
	virtual void AddInitializeOperation(); 
	virtual void AddInsertOperation(); 
	virtual void AddDeleteOperation();
protected:
	virtual void AddNoFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::function<void()> action);
	virtual void AddIntFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::vector<InputData> InputBoxs,
		std::function<void(std::map <std::string, std::string>)> action);
private:
	Visualize::VisualScene scene;
	Visualize::Visualization mVisualization;
	Algorithms::AVL mAlgo; 
};

