#pragma once
#include "SceneNode.h"
#include "CircularNode.h"
#include "Edge.h"
#include "SquareNode.h"
#include "../Helper/ColorSetting.h"
#include "../Helper/Helper.h"

#include <map>
#include <vector>
#include <set>

namespace Visualize
{
	class VisualScene
	{
	public:
		VisualScene(); 
		~VisualScene(); 

		static VisualScene transitionScene(const VisualScene& fromScene, const VisualScene& toScene,
			float time, float tottalTime); 

		static float easeInOut(float from, float to, float time, float totalTime);
		
		void draw(); 
		void update(float dt);

		int createCirNode(int value); 
		int createCharNode(std::string value);
		void moveCirNode(int id, Vector2 position); 
		void colorCirNode(int id, Color color);
		void highlightCirNode(int id); 
		void unhighlightCirNode(int id); 
		void resetColorCirNode(int id);
		void updateCirNode(int id, int value); 
		void removeCirNode(int id); 
		void setLabel(int id, std::string label);
		Vector2 getCirNodePosition(int id) const;
		bool getMouseHover(int id); 

		int createEdge(Vector2 source, Vector2 des); 
		int createEdgeOffSet(Vector2 source, Vector2 des, int offset = 0); 
		void colorEdge(int id, Color color);
		void moveEdgeSource(int id, Vector2 source);
		void moveEdgeDes(int id, Vector2 des); 
		void setWeight(int id, std::string weight);
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
		void eraseValue(int id, int value);
		void addValue(int id, int value);
		void updateValue(int id, int oldValue, int newValue);
		void highlightBlock(int id);
		void unhighlightBlock(int id);
		Vector2 getBlockPos(int id, int index) const;
		Vector2 getBlockMid(int id) const;

		void resetColor(); 
		void resetLabel();

	private:
		Visualize::CircularNode& getCirNode(int id); 
		const Visualize::CircularNode& getCirNode(int id) const; 

		Visualize::Edge& getEdge(int id); 
		const Visualize::Edge& getEdge(int id) const;

		Visualize::SquareNode& getSquareNode(int id); 
		const Visualize::SquareNode& getSquareNode(int id) const;

		static Color easeInOutColor(Color fromColor, Color toColor,
			float time, float totalTime);

		static void transitionCirNode(const VisualScene& fromScene, const VisualScene& toScene,
			float time, float totalTime, VisualScene& sceneRes); 

		static void transitionEdge(const VisualScene& fromScene, const VisualScene& toScene,
			float time, float totalTime, VisualScene& sceneRes);

		static void transitionSquareNode(const VisualScene& fromScene, const VisualScene& toScene, 
			float time, float totalTime, VisualScene& sceneRes);

	private: 
		std::map<int, CircularNode> mCirNodeMap;
		std::map<int, Edge> mEdgeMap;
		std::map<int, SquareNode> mSquareMap;
	};
}

