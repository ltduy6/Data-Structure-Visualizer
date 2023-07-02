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
		void unPackAll();

		virtual void draw(Vector2 basePos = Vector2{0, 0});
		virtual void update(float dt);
		virtual bool isSelectable() const; 

		virtual void drawCurrent(Vector2 basePos);
		virtual void ToggleActive();
		std::vector<GUI::Component::Ptr> getChildren();
		virtual bool getHoverStatus();

		void SetActive(bool active);
	protected:
		std::vector<GUI::Component::Ptr> mChildren;
	};
}

