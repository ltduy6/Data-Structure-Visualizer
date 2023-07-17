#pragma once
#include "SceneNode.h"
#include "CircularNode.h"
#include "Edge.h"
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

		int createCirNode(int value); 
		void moveCirNode(int id, Vector2 position); 
		void moveCirNodeDelta(int id, Vector2 position); 
		void colorCirNode(int id, Color color);
		void highlightCirNode(int id); 
		void unhighlightCirNode(int id); 
		void resetColorCirNode(int id);
		void updateCirNode(int id, int value); 
		void removeCirNode(int id); 
		Vector2 getCirNodePosition(int id) const;

		int createEdge(Vector2 source, Vector2 des); 
		void moveEdgeSource(int id, Vector2 source);
		void moveEdgeDes(int id, Vector2 des); 
		void moveEdgeDelta(int id, Vector2 source, Vector2 des);
		void highlightEdge(int id); 
		void unhighlightEdge(int id);
		void removeEdge(int id);

		void resetColor(); 

	private:
		Visualize::CircularNode& getCirNode(int id); 
		const Visualize::CircularNode& getCirNode(int id) const; 

		Visualize::Edge& getEdge(int id); 
		const Visualize::Edge& getEdge(int id) const;

		static Color easeInOutColor(Color fromColor, Color toColor,
			float time, float totalTime);

		static void transitionCirNode(const VisualScene& fromScene, const VisualScene& toScene,
			float time, float totalTime, VisualScene& sceneRes); 

		static void transitionEdge(const VisualScene& fromScene, const VisualScene& toScene,
			float time, float totalTime, VisualScene& sceneRes);
	private: 
		std::map<int,CircularNode> mCirNodeMap;
		std::map<int, Edge> mEdgeMap;
	};
}

