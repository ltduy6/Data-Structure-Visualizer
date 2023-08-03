#pragma once

#include "VisualScene.h"
#include "SceneNode.h"
#include "ControlScene.h"
#include "CodeHighLight.h"

#include "raylib.h"

#include <vector>

namespace Visualize {
	class Visualization 
	{
	public:
		Visualization(); 
		~Visualization();

		void draw(); 
		void update(float dt); 

		void createNewScene(); 
		Visualize::VisualScene getLastScene() const; 
		void reset(VisualScene initScene = VisualScene());

		int createCirNode(int value);
		int createCharNode(std::string value);
		void moveCirNode(int id, Vector2 position);
		void moveCirNodeDelta(int id, Vector2 position);
		void colorCirNode(int id, Color color);
		void highlightCirNode(int id);
		void unhighlightCirNode(int id);
		void resetColorCirNode(int id);
		void updateCirNode(int id, int value);
		void removeCirNode(int id);
		void setLabel(int id, std::string label);
		Vector2 getCirNodePosition(int id) const;

		int createEdge(Vector2 source, Vector2 des);
		int createEdgeOffSet(Vector2 source, Vector2 des, int offset = 0);
		void colorEdge(int id, Color color);
		void setWeight(int id, std::string weight);
		void moveEdgeSource(int id, Vector2 source);
		void moveEdgeDes(int id, Vector2 des);
		void moveEdgeDelta(int id, Vector2 source, Vector2 des);
		void highlightEdge(int id);
		void unhighlightEdge(int id);
		void removeEdge(int id);
		bool isEdgeExist(int id);
		Color getEdgeColor(int id) const;
		Vector2 getEdgeSource(int id);
		Vector2 getEdgeDes(int id);

		int createBlock(std::vector<int> list);
		void moveBlock(int id, Vector2 position);
		void removeBlock(int id);
		void setLabelBlock(int id, std::string label);
		void highlightBlock(int id);
		void unhighlightBlock(int id);
		void eraseValue(int id, int value);
		void addValue(int id, int value);
		void updateValue(int id, int oldValue, int newValue);
		Vector2 getBlockPos(int id, int index) const;
		Vector2 getBlockMid(int id) const;

		void resetColor();
		void resetLabel();
		void addCode(std::string code); 
		void highlightCode(std::vector<int> lines);

		bool getHoverStatus() const;

	private:
		std::vector<VisualScene> mContainer; 
		VisualScene mDisplayScene; 
		ControlScene mControl; 
		CodeHighLight mCodeHighlight;
	};
}

