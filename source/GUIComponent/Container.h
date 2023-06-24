#pragma once
#include "Component.h"
#include <memory>
#include <vector>

namespace GUI {
	class Container : public Component
	{
	public:
		typedef std::shared_ptr<Container> Ptr; 
	public:
		Container();

		void pack(Component::Ptr component);
		void unpack();

		virtual void draw(Vector2 basePos); 
		virtual bool isSelectable() const; 

		virtual void drawCurrent(Vector2 basePos);

		virtual Vector2 Getsize(); 
	protected:
		std::vector<Component::Ptr> mChildren;
	};
}

