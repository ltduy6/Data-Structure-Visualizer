#pragma once
#include "../Visualization/Visualization.h"

namespace Algorithms
{
	class Algorithm
	{
	public:
		Algorithm(Visualize::Visualization& visualization); 
		~Algorithm(); 
	protected:
		Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH * Helper::scaleFactorX() / 2, 200 * Helper::scaleFactorY()};
	protected:
		virtual void sceneReset();
		virtual void sceneInit();
		void newScene(std::vector<int> lines);
	protected: 
		Visualize::Visualization& mVisualization;
	};
}

