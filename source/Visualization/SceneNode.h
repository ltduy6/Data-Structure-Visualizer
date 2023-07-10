#pragma once

#include "../NonCopyable.hpp"
#include "raylib.h"
#include <memory>

namespace Visualize {
	class SceneNode
	{
	public:
		std::shared_ptr<SceneNode> Ptr;
		float OUTLINE_THICKNESS = 5;
		float ROUND_SEGMENT = 10; 
	public:
		SceneNode();
		virtual ~SceneNode();

		virtual void draw() = 0;

		virtual void SetPosition(Vector2 pos);
		Vector2  GetPosition() const;

		virtual void SetScale(float scale);
		float GetScale() const;

		int getObjectId() const;
	private:
		Vector2 mPos{ Vector2 {0, 0} };
		float mScale{ 1 };
		static int objectID; 
	};
}

