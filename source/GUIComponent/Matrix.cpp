#include "Matrix.h"
#include <iostream>

GUI::Matrix::Matrix()
{
}

GUI::Matrix::~Matrix()
{
}

void GUI::Matrix::draw(Vector2 base)
{
	if (this->GetActive())
	{
		for (auto row : this->firstRow)
		{
			row.draw(); 
		}
		for (auto col : this->firstCol)
			col.draw();
		for (auto row : this->mMatrix)
			for (auto ceil : row)
				ceil->draw();
	}
}

void GUI::Matrix::update(float dt)
{
	if (this->GetActive())
	{
		for (auto row : this->mMatrix)
			for (auto ceil : row)
			{
				ceil->update(dt);
			}
		for (auto row : this->mMatrix)
			for (auto ceil : row)
				if (ceil->getHoverStatus())
				{
					this->isHover = true; 
					return;
				}
		this->isHover = false;
	}
}

void GUI::Matrix::create(int size)
{
	// clear matrix first
	for (auto& row : this->mMatrix)
		row.clear();
	this->mMatrix.clear();
	this->firstCol.clear();
	this->firstRow.clear();
	this->mSize = 0;
	// create new matrix
	this->mSize = size;
	for (int i = 0; i < size; ++i)
	{
		Button ceilRow; 
		ceilRow.SetSize({ 70, 70 });
		ceilRow.SetPos({ this->mPos.x + i * 70, this->mPos.y - 70});
		ceilRow.setText(std::to_string(i));
		ceilRow.setTextAlignment(Button::TextAlignMent::Center);

		Button ceilCol; 
		ceilCol.SetSize({ 70, 70 });
		ceilCol.SetPos({ this->mPos.x - 70, this->mPos.y + i * 70 });
		ceilCol.setText(std::to_string(i));
		ceilCol.setTextAlignment(Button::TextAlignMent::Center);

		this->firstRow.push_back(ceilRow); 
		this->firstCol.push_back(ceilCol);
	}
	for (int i = 0; i < size; ++i)
	{
		std::vector<InputBox::Ptr> row; 
		for (int j = 0; j < size; ++j)
		{
			GUI::InputBox::Ptr ceil(new GUI::InputBox());
			ceil->SetSize({ 70,70 });
			ceil->SetPos({ this->mPos.x + j * 70, this->mPos.y + i * 70});
			ceil->SetLabel("");
			row.push_back(ceil);
		}
		this->mMatrix.push_back(row);
	}
}

int GUI::Matrix::GetMatrixSize() const
{
	return this->mSize;
}

bool GUI::Matrix::getHoverStatus()
{
	return this->isHover;
}

std::map<std::string, std::string> GUI::Matrix::extractInput()
{
	std::map<std::string, std::string> inputs;
	for (int i = 0; i < this->mSize; ++i)
	{
		for (int j = 0; j < this->mSize; ++j)
		{
			inputs[std::to_string(i) + std::to_string(j)] = this->mMatrix[i][j]->getInputText();
		}
	}
	return inputs;
}
