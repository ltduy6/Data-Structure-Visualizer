#pragma once

#include "State.h"
#include "../GUIComponent/ActionsList.h"
#include "../GUIComponent/ActionsContainer.h"
#include "../GUIComponent/InputBox.h"
#include "../GUIComponent/OptionInputField.h"
#include "../GUIComponent/NavigationBar.h"
#include "../GUIComponent/Matrix.h"
#include "../Include/tinyfiledialogs.h"
#include "../Helper/GlobalVar.h"
#include "../Visualization/CircularNode.h"
#include "../Visualization/VisualScene.h"
#include "../Visualization/Visualization.h"
#include "../Core/AVL.h"
#include "../Core/Btree.h"
#include "../Core/Heap.h"
#include "../Core/Trie.h"
#include "../Core/Graph.h"
#include "../Core/HashTable.h"

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
	virtual void IniNavBar();
	virtual void UpdateMouseCursor();
	virtual void handleDraging(); 
protected:
	GUI::ActionsList actionList;
	GUI::NavigationBar navBar;
	Visualize::Visualization mVisualization;
	GUI::Matrix matrix;
};


