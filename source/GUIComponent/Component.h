#pragma once

#include "raylib.h"
#include <memory>
#include <map>
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
	protected:
		virtual bool getHoverStatus(std::map<std::string, Rectangle> bounds, bool Hover, bool nonHover);
		virtual bool getHoverStatus(Rectangle bound, bool Hover, bool nonHover);
	protected:
		Vector2 mPos;
		bool mIsActive;
	private:
		bool mIsSelected; 
	};
}

