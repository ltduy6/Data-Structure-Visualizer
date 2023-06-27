#pragma once

#include "raylib.h"
#include <memory>
#include <vector>
#include <string>

namespace GUI {
	class Component
	{
	public: 
		typedef std::shared_ptr<Component> Ptr;
	public:
		Component(); 
		virtual ~Component();
		virtual void draw(Vector2 basePos = Vector2{0, 0}) = 0;
		virtual void update(float dt) = 0;
		virtual bool isSelectable() const = 0; 
		bool isSelected() const; 
		virtual void select(); 
		virtual void deSelect(); 

		virtual void ToggleActive(); 
		virtual void SetActive(bool active);
		virtual bool GetActive(); 
	public:
		void SetPos(Vector2 pos); 
		Vector2 GetPos(); 
		virtual Vector2 GetSize(); 
		virtual Rectangle GetRec();
	public:
		virtual bool getHoverStatus();
	protected:
		Vector2 mPos{ Vector2 {0, 0} };
		Rectangle mRect{ Rectangle {0, 0, 0, 0} };
		bool mIsActive{ true };
	private:
		bool mIsSelected{ false };
	};
}

