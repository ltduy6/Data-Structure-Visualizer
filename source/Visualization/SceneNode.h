#pragma once

#include "raylib.h"
#include "../Helper/GlobalVar.h"
#include <memory>

namespace Visualize {
	class SceneNode
	{
	public:
		std::shared_ptr<SceneNode> Ptr;
		float OUTLINE_THICKNESS = 5;
		float ROUND_SEGMENT = 10; 
		static constexpr int ELEMENT_SIZE = 60;
	public:
		SceneNode();
		virtual ~SceneNode();

		virtual void draw() = 0;

		virtual void SetPosition(Vector2 pos);
		Vector2  GetPosition() const;

		virtual void SetScale(float scale);
		float GetScale() const;
		virtual int getObjectId() const = 0;
	protected:
		Vector2 mPos{ Vector2 {0, 0} };
		float mScale{ 1 };
		static int objectID_CIRNODE;
		static int objectID_EDGE; 
		static int objectID_SQUARE;
	};
}

