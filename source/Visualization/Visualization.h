#pragma once

#include "VisualScene.h"
#include "SceneNode.h"

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
		void moveCirNode(int id, Vector2 position);
		void moveCirNodeDelta(int id, Vector2 position);
		void colorCirNode(int id, Color color);
		void highlightCirNode(int id);
		void unhighlightCirNode(int id);
		void updateCirNode(int id, int value);
		void removeCirNode(int id);
		Vector2 getCirNodePosition(int id) const;


	private:
		std::vector<VisualScene> mContainer; 
		VisualScene mDisplayScene; 
	};
}

