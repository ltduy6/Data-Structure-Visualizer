#include "HashTable.h"

Algorithms::HashTable::HashTable(Visualize::Visualization& visualization) : Algorithm(visualization)
{
}

Algorithms::HashTable::~HashTable()
{
}

void Algorithms::HashTable::Create(int size, int numValues)
{
	this->sceneReset();
	this->mTable.resize(size);
	this->mSize = size;
	for (int i = 0; i < size; ++i)
	{
		this->mTable[i].first = -1; 
		this->mTable[i].second = this->mVisualization.createCirNode(-1);
		this->mVisualization.setLabel(this->getVisualId(i), std::to_string(i));
		if (size < 12)
		{
			this->mVisualization.moveCirNode(this->getVisualId(i), STARTING_POINT + Vector2{HORIZONTAL_SPACE, 0} *(i - size / 2));
		}
		else {
			int tempSize = 11; 
			if (i < tempSize)
				this->mVisualization.moveCirNode(this->getVisualId(i), STARTING_POINT + Vector2{HORIZONTAL_SPACE, 0} *(i - tempSize / 2));
			else {
				int prevCeil = i - 11; 
				this->mVisualization.moveCirNode(this->getVisualId(i), this->mVisualization.getCirNodePosition(this->getVisualId(prevCeil)) + Vector2{ 0, VERTICAL_SPACE });
			}
		}
	}
	for (int i = 0; i < numValues; ++i)
	{
		int newValue = Helper::rand(1, 99);
		int ind = this->hashFunc(newValue);
		while (this->getValueId(ind) != -1)
		{
			ind = (ind + 1) % this->mSize;
		}
		this->mTable[ind].first = newValue;
		this->mVisualization.updateCirNode(this->getVisualId(ind), newValue);
	}
}

void Algorithms::HashTable::InitFromFile(std::vector<int>& input)
{
	this->sceneReset();
	this->mSize = input[0]; 
	this->mTable.resize(this->mSize);

	for (int i = 0; i <	this->mSize; ++i)
	{
		this->mTable[i].first = -1;
		this->mTable[i].second = this->mVisualization.createCirNode(-1);
		this->mVisualization.setLabel(this->getVisualId(i), std::to_string(i));
		if (this->mSize < 12)
		{
			this->mVisualization.moveCirNode(this->getVisualId(i), STARTING_POINT + Vector2{ HORIZONTAL_SPACE, 0 } *(i - this->mSize / 2));
		}
		else {
			int tempSize = 11;
			if (i < tempSize)
				this->mVisualization.moveCirNode(this->getVisualId(i), STARTING_POINT + Vector2{ HORIZONTAL_SPACE, 0 } *(i - tempSize / 2));
			else {
				int prevCeil = i - 11;
				this->mVisualization.moveCirNode(this->getVisualId(i), this->mVisualization.getCirNodePosition(this->getVisualId(prevCeil)) + Vector2{ 0, VERTICAL_SPACE });
			}
		}
	}

	for (int i = 1; i < input.size(); ++i)
	{
		int ind = hashFunc(input[i]);

		while (this->getValueId(ind) != -1 && this->getValueId(ind) != -2)
		{
			ind = (ind + 1) % this->mSize;
		}
		if (this->getValueId(ind) == -1 || this->getValueId(ind) == -2)
		{
			this->mVisualization.updateCirNode(this->getVisualId(ind), input[i]);
			this->mTable[ind].first = input[i];
		}
	}
}

void Algorithms::HashTable::Insert(int value)
{
	this->sceneInit();
	this->mVisualization.addCode("if N + 1 == M, prevent insertion");
	this->mVisualization.addCode("step = 0; i = base = key%HT.length;"); 
	this->mVisualization.addCode("while (HT[i] != EMPTY && HT[i] != DELETED)");
	this->mVisualization.addCode("	  ++step; i = (base+step*1)%HT.length");
	this->mVisualization.addCode("found insertion point, insert key at HT[i]");

	int currSize = 0;
	for (auto ceil : this->mTable)
		if (ceil.first != -1 && ceil.first != -2)
			currSize++;

	if (currSize + 1 == this->mSize)
	{
		this->newScene({ 0 }); 
		return;
	}

	int ind = hashFunc(value);

	this->newScene({ 1 });
	this->mVisualization.highlightCirNode(this->getVisualId(ind));
	while (this->getValueId(ind) != -1 && this->getValueId(ind) != -2)
	{
		this->newScene({2}); 
		this->mVisualization.unhighlightCirNode(this->getVisualId(ind));
		ind = (ind + 1) % this->mSize;
		this->newScene({ 3 });
		this->mVisualization.highlightCirNode(this->getVisualId(ind));
	}
	if (this->getValueId(ind) == -1 || this->getValueId(ind) == -2)
	{
		this->newScene({4}); 
		this->mVisualization.unhighlightCirNode(this->getVisualId(ind));
		this->mVisualization.updateCirNode(this->getVisualId(ind), value);
		this->mTable[ind].first = value;
	}
}

void Algorithms::HashTable::Remove(int value)
{
	this->sceneInit(); 
	this->mVisualization.addCode("step = 0; i = base = key%HT.length;");
	this->mVisualization.addCode("while (true)");
	this->mVisualization.addCode("	 if (HT[i] == EMPTY) break // if (HT[i] == EMPTY)");
	this->mVisualization.addCode("	 else if (HT[i] == key) // else if (HT[i] == key)");
	this->mVisualization.addCode("	    HT[i] = DELETED, break // HT[i] = DELETED");
	this->mVisualization.addCode("	 else ++step; i = (base+step*1)%HT.length");

	int ind = hashFunc(value); 

	this->newScene({ 0 });
	this->mVisualization.highlightCirNode(this->getVisualId(ind));

	while (this->getValueId(ind) != value)
	{
		if (this->getValueId(ind) == -1)
		{
			this->newScene({ 2 }); 
			return;
		}
		this->newScene({5});
		this->mVisualization.unhighlightCirNode(this->getVisualId(ind));
		ind = (ind + 1) % this->mSize;
		this->mVisualization.highlightCirNode(this->getVisualId(ind));
	}
	if (this->getValueId(ind) == value)
	{
		this->newScene({3, 4});
		this->mVisualization.updateCirNode(this->getVisualId(ind), -2);
		this->mTable[ind].first = -2;
	}
}

void Algorithms::HashTable::Search(int value)
{
	this->sceneInit(); 
	this->mVisualization.addCode("step = 0; i = base = key%HT.length;"); 
	this->mVisualization.addCode("while (true)");
	this->mVisualization.addCode("	if (HT[i] == EMPTY) return 'not found'");
	this->mVisualization.addCode("	else if (HT[i] == key) return 'found at index i'");
	this->mVisualization.addCode("	else ++step; i = (base+step*1)%HT.length");

	int ind = hashFunc(value);

	this->newScene({ 0 });
	this->mVisualization.highlightCirNode(this->getVisualId(ind));

	while (true)
	{
		if (this->getValueId(ind) == -1)
		{
			this->newScene({2});
			return;
		}
		if (this->getValueId(ind) == value)
		{
			this->newScene({ 3 }); 
			return;
		}
		this->newScene({4});
		this->mVisualization.unhighlightCirNode(this->getVisualId(ind));
		ind = (ind + 1) % this->mSize;
		this->mVisualization.highlightCirNode(this->getVisualId(ind));
	}


}

int Algorithms::HashTable::getSize() const
{
	return this->mSize;
}

void Algorithms::HashTable::sceneReset()
{
	this->mVisualization.reset();
	this->mTable.clear();
}

void Algorithms::HashTable::sceneInit()
{
	mVisualization.reset(mVisualization.getLastScene());
	this->mVisualization.resetColor();
}

int Algorithms::HashTable::hashFunc(int value)
{
	return value % this->mSize;
}

int Algorithms::HashTable::getVisualId(int index)
{
	return this->mTable[index].second;
}

int Algorithms::HashTable::getValueId(int index)
{
	return this->mTable[index].first;
}
