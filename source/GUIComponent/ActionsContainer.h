#pragma once

#include "Container.h"
#include <memory>

namespace GUI {
	class ActionsContainer : public Container
	{
	public:
		typedef std::shared_ptr<ActionsContainer> Ptr;
		ActionsContainer();
		~ActionsContainer();

		void drawCurrent(Vector2 base = Vector2{0, 0});
		void SetActive(bool active);
	private:
		void updatePos(Vector2 base);
	};
}

