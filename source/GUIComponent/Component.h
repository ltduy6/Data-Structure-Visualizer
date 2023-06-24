#pragma once

#include "raylib.h"
#include <memory>

namespace GUI {
	class Component
	{
	public: 
		typedef std::shared_ptr<Component> Ptr;
	public:
		Component(); 
		virtual ~Component();
		virtual void draw(Vector2 basePos) = 0;
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
	protected:
		Vector2 mPos;
		bool mIsActive;
	private:
		bool mIsSelected; 
	};
}

