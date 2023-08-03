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
		static constexpr Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH / 2, 200 };
	protected:
		virtual void sceneReset();
		virtual void sceneInit();
		void newScene(std::vector<int> lines);
	protected: 
		Visualize::Visualization& mVisualization;
	};
}

