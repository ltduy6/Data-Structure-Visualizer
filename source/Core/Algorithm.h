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
		void sceneReset();
		void sceneInit();
		void newScene(std::vector<int> lines);
	protected: 
		Visualize::Visualization& mVisualization;
	};
}

