#pragma once
#include "Component.h"
#include "raylib.h"

#include <functional>
#include <map>
#include <memory>
#include <string>

namespace GUI {
	class ActionBox : public Component
	{
	public:
		static constexpr int INPUT_LABEL_SIZE = 19; 
	public:
		struct Input {
			std::string label;
			std::string name;
			std::function<bool(std::string)> validator;
			int width;
			Input(std::string label, std::string name, std::function<bool(std::string)> validator, int width); 
		};
		typedef std::map<std::string, std::string> InputData; 
	public:
		ActionBox();
		void update(float dt); 
		void draw(Vector2 base); 

		void activate(); 
		void deactivate(); 


	};
}

