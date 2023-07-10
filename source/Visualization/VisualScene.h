#pragma once
#include "SceneNode.h"
#include "CircularNode.h"
#include "../Helper/ColorSetting.h"

#include <map>
#include <vector>

namespace Visualize
{
	class VisualScene
	{
	public:
		VisualScene(); 
		~VisualScene(); 

		void draw(); 

		int createCirNode(int value); 
		void moveCirNode(int id, Vector2 position); 
		void moveCirNodeDelta(int id, Vector2 position); 
		void colorCirNode(int id, Color color);
		void highlightCirNode(int id); 
		void unhighlightCirNode(int id); 
		void updateCirNode(int id, int value); 
		void removeCirNode(int id); 
		Vector2 getCirNodePosition(int id) const;

	private:
		Visualize::CircularNode& getCirNode(int id); 
		const Visualize::CircularNode& getCirNode(int id) const; 
	private: 
		std::map<int,CircularNode> mCirNodeMap;
	};
}

