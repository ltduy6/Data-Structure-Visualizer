#pragma once
#include "SceneNode.h"
#include "../Helper/Helper.h"
namespace Visualize {
	class Edge : public SceneNode
	{
	public:
		static constexpr int THICKNESS = 5; 
		static constexpr int OFFSET = 30; 
	public:
		Edge(); 
		~Edge(); 
	public:
		virtual void draw(); 

		void SetSource(Vector2 pos); 
		Vector2 GetSource() const; 

		void SetDestination(Vector2 pos); 
		Vector2 GetDestination() const; 
	private:
		Vector2 mSource{ Vector2 {50, 50} }; 
		Vector2 mDes{ Vector2 {100, 100} };
	};
}

