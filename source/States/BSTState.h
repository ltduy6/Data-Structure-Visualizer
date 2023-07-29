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
#include "../Core/Btree.h"
#include "../Core/Heap.h"
#include "../Core/Trie.h"
#include "../Core/Graph.h"

class BSTState : public State
{
public:
	struct InputData {
		float width;
		std::string label;
		int minValue; 
		int maxValue; 
	};
public:
	BSTState(StateStack& stack, Context context); 
	virtual void draw();
	virtual bool update(float dt); 
protected:
	virtual void AddNoFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::function<void()> action);
	virtual void AddIntFieldInput(GUI::ActionsContainer::Ptr container, std::string title, std::vector<InputData> InputBoxs,
		std::function<void(std::map <std::string, std::string>)> action);
protected:
	GUI::ActionsList actionList;
	Visualize::Visualization mVisualization;
};

