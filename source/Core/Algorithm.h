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
		Visualize::Visualization& mVisualization;
	};
}

