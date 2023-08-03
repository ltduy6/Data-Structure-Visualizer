#pragma once
#include "InputBox.h"
#include "Container.h"

namespace GUI {
	class Matrix : public Component
	{
	public:
		Matrix();
		~Matrix();
	public:
		void draw(Vector2 base = {0, 0});
		void update(float dt);
		void create(int size);
		int GetMatrixSize() const; 
		bool getHoverStatus();
		std::map<std::string, std::string> extractInput(); 
	private:
		int mSize{ 0 };
		bool isHover{ true };
		std::vector<std::vector<InputBox::Ptr>> mMatrix;
		std::vector<Button> firstRow;
		std::vector<Button> firstCol;
	};
}
