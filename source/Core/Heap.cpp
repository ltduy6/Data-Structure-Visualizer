#include "Heap.h"
#include <cmath>
#include <iostream>

Algorithms::Heap::Heap(Visualize::Visualization& visualization) : Algorithm(visualization)
{
	this->setMaxHeap();
}

Algorithms::Heap::~Heap()
{
}

void Algorithms::Heap::InitRandomFixSize(int size)
{
	std::vector<int> list;
	int i = 0;
	while (i < size)
	{
		int rand = Helper::rand(1, 99);
		if (Helper::checkExist(list, rand) == false)
		{
			list.push_back(rand);
			i++;
		}
	}
	this->Init(list);
}

void Algorithms::Heap::Init(std::vector<int>& list)
{
	this->sceneReset();
	for (int value : list)
		this->insertNonAnimation(value);
}

void Algorithms::Heap::Insert(int value)
{
	this->sceneInit();
	if (this->isMaxHeap)
	{
		this->mVisualization.addCode("A[A.length] = v");
		this->mVisualization.addCode("i = A.length - 1");
		this->mVisualization.addCode("while ((i > 1) && (A[i] > A[parent(i)]))");
		this->mVisualization.addCode("swap(A[i], A[parent(i)]); i = parent(i)");
	}
	else {
		this->mVisualization.addCode("A[A.length] = v");
		this->mVisualization.addCode("i = A.length - 1");
		this->mVisualization.addCode("while ((i > 1) && (A[i] < A[parent(i)]))");
		this->mVisualization.addCode("swap(A[i], A[parent(i)]); i = parent(i)");
	}
	this->newScene({});
	this->insertAnimation(value);
	this->newScene({});
	this->mVisualization.resetColor();
}

void Algorithms::Heap::Remove(int index)
{
	this->sceneInit(); 
	if (this->isMaxHeap)
	{
		this->mVisualization.addCode("A[i] = A[1]+1; shiftup(i); // new max/root"); // 0
		this->mVisualization.addCode("take out A[1]");								// 1
		this->mVisualization.addCode("A[1] = A[A.length-1]");						// 2
		this->mVisualization.addCode("i = 1; A.length--");							// 3
		this->mVisualization.addCode("while (i < A.length)");						// 4
		this->mVisualization.addCode("if A[i] < (L = the larger of i's children)"); // 5
		this->mVisualization.addCode("swap(A[i], L); i = L's index");				// 6
	}
	else {
		this->mVisualization.addCode("A[i] = A[1]+1; shiftup(i); // new max/root"); // 0
		this->mVisualization.addCode("take out A[1]");								// 1
		this->mVisualization.addCode("A[1] = A[A.length-1]");						// 2
		this->mVisualization.addCode("i = 1; A.length--");							// 3
		this->mVisualization.addCode("while (i < A.length)");						// 4
		this->mVisualization.addCode("if A[i] > (L = the larger of i's children)"); // 5
		this->mVisualization.addCode("swap(A[i], L); i = L's index");				// 6
	}
	this->deleteAnimation(index);
	this->newScene({}); 
	this->mVisualization.resetColor();
}

void Algorithms::Heap::Search(int value)
{
}

int Algorithms::Heap::getSize() const
{
	int size = this->mHeap.size(); 
	return size; 
}

void Algorithms::Heap::sceneReset()
{
	this->mVisualization.reset();
	for (auto node : this->mHeap)
		delete node; 
	this->mHeap.clear();
}

void Algorithms::Heap::insertAnimation(int value)
{
	Node* newNode = new Node(value);
	newNode->id = this->mVisualization.createCirNode(value);
	newNode->value = value;
	this->mHeap.push_back(newNode);
	int index = this->mHeap.size() - 1;

	this->mVisualization.setLabel(newNode->id, std::to_string(index + 1));
	if (index == 0)
	{
		this->mVisualization.moveCirNode(newNode->id, STARTING_POINT);
		this->mVisualization.highlightCirNode(newNode->id); 
	}
	else {
		int level = static_cast<int>(log2(index + 1));
		float horizontal = HORIZONTAL_SPACE / (1 << level);
		Vector2 pos = this->getPos(parent(index));

		if (index & 1)
		{
			pos = pos + Vector2{ -horizontal,  VERTICAL_SPACE }; 

			this->mVisualization.moveCirNode(this->mHeap[index]->id, pos);
			this->mVisualization.highlightCirNode(newNode->id);

			this->newScene({0, 1});
			this->mHeap[parent(index)]->idEdgeLeft = this->mVisualization.createEdge(
				this->getPos(parent(index)), this->getPos(index));
		}
		else
		{
			pos = pos + Vector2{ horizontal,  VERTICAL_SPACE };

			this->mVisualization.moveCirNode(this->mHeap[index]->id, pos);
			this->mVisualization.highlightCirNode(newNode->id);

			this->newScene({0, 1});
			this->mHeap[parent(index)]->idEdgeRight = this->mVisualization.createEdge(
				this->getPos(parent(index)), this->getPos(index));
		}
		this->upHeapAnimation(index, {2, 3});
	}
}

void Algorithms::Heap::insertNonAnimation(int value)
{
	Node* newNode = new Node(value);
	newNode->id = this->mVisualization.createCirNode(value);
	newNode->value = value;
	this->mHeap.push_back(newNode);
	int index = this->mHeap.size() - 1;

	this->mVisualization.setLabel(newNode->id, std::to_string(index + 1));
	if (index == 0)
	{
		this->mVisualization.moveCirNode(newNode->id, STARTING_POINT);
	}
	else {
		int level = static_cast<int>(log2(index + 1));
		float horizontal = HORIZONTAL_SPACE / (1 << level);
		Vector2 pos = this->getPos(parent(index));

		if (index & 1)
		{
			pos = pos + Vector2{ -horizontal,  VERTICAL_SPACE };

			this->mVisualization.moveCirNode(this->mHeap[index]->id, pos);

			this->mHeap[parent(index)]->idEdgeLeft = this->mVisualization.createEdge(
				this->getPos(parent(index)), this->getPos(index));
		}
		else
		{
			pos = pos + Vector2{ horizontal,  VERTICAL_SPACE };

			this->mVisualization.moveCirNode(this->mHeap[index]->id, pos);

			this->mHeap[parent(index)]->idEdgeRight = this->mVisualization.createEdge(
				this->getPos(parent(index)), this->getPos(index));
		}
		this->upHeapNonAnimation(index);
	}
}

void Algorithms::Heap::deleteAnimation(int index)
{
	if (this->mHeap.empty())
		return; 
	this->newScene({0});
	Node* currNode = this->mHeap[index - 1];
	this->mVisualization.highlightCirNode(currNode->id); 
	this->mVisualization.updateCirNode(currNode->id, this->mHeap[0]->value + 1); 
	this->mHeap[index - 1]->value = this->mHeap[0]->value + 1;
	this->upHeapAnimation(index - 1, {0, 0});
	this->extractMax();
}

void Algorithms::Heap::upHeapAnimation(int index, std::vector<int> line)
{
	while (index > 0 && this->largerThan(this->mHeap[index]->value, this->mHeap[parent(index)]->value))
	{
		std::swap(this->mHeap[index]->value, this->mHeap[parent(index)]->value);
		this->newScene({line[0]});
		this->mVisualization.unhighlightCirNode(this->mHeap[parent(index)]->id);
		
		// Swap node animation
		this->newScene({line[1]});
		Vector2 tempPos = this->getPos(index); 

		this->mVisualization.moveCirNode(
			this->mHeap[index]->id, this->getPos(parent(index)));

		this->mVisualization.moveCirNode(this->mHeap[parent(index)]->id, tempPos);

		// Swap label
		this->mVisualization.setLabel(this->mHeap[index]->id, std::to_string(parent(index) + 1));
		this->mVisualization.setLabel(this->mHeap[parent(index)]->id, std::to_string(index + 1));
		this->mVisualization.resetColor(); 
		this->mVisualization.highlightCirNode(this->mHeap[index]->id);

		// Swap id visualization
		std::swap(this->mHeap[index]->id, this->mHeap[parent(index)]->id);

		// move to parent
		index = parent(index);
	}
}

void Algorithms::Heap::upHeapNonAnimation(int index)
{
	while (index > 0 && this->largerThan(this->mHeap[index]->value, this->mHeap[parent(index)]->value))
	{
		std::swap(this->mHeap[index]->value, this->mHeap[parent(index)]->value);

		// Swap node animation
		Vector2 tempPos = this->getPos(index);

		this->mVisualization.moveCirNode(
			this->mHeap[index]->id, this->getPos(parent(index)));

		this->mVisualization.moveCirNode(this->mHeap[parent(index)]->id, tempPos);

		// Swap label
		this->mVisualization.setLabel(this->mHeap[index]->id, std::to_string(parent(index) + 1));
		this->mVisualization.setLabel(this->mHeap[parent(index)]->id, std::to_string(index + 1));

		// Swap id visualization
		std::swap(this->mHeap[index]->id, this->mHeap[parent(index)]->id);

		// move to parent
		index = parent(index);
	}
}

void Algorithms::Heap::downHeapAnimation(int index)
{
	int largest = index; 
	int leftChild = left(index); 
	int rightChild = right(index); 
	
	if (leftChild < this->mHeap.size() && this->largerThan(this->mHeap[leftChild]->value, this->mHeap[largest]->value))
		largest = leftChild;
	
	if (rightChild < this->mHeap.size() && this->largerThan(this->mHeap[rightChild]->value, this->mHeap[largest]->value))
		largest = rightChild;

	if (largest != index)
	{
		std::swap(this->mHeap[index]->value, this->mHeap[largest]->value); 

		this->newScene({5}); 
		this->mVisualization.unhighlightCirNode(this->mHeap[largest]->id); 

		this->newScene({6}); 
		Vector2 tempPos = this->getPos(index); 
		this->mVisualization.moveCirNode(this->mHeap[index]->id, this->getPos(largest)); 
		this->mVisualization.moveCirNode(this->mHeap[largest]->id, tempPos);

		this->mVisualization.setLabel(this->mHeap[index]->id, std::to_string(largest + 1)); 
		this->mVisualization.setLabel(this->mHeap[largest]->id, std::to_string(index + 1));

		this->mVisualization.resetColor(); 
		this->mVisualization.highlightCirNode(this->mHeap[index]->id);

		std::swap(this->mHeap[index]->id, this->mHeap[largest]->id);


		this->downHeapAnimation(largest);
	}
}

void Algorithms::Heap::extractMax()
{
	int lastIndex = this->mHeap.size() - 1; 
	Vector2 rootPos = this->getPos(0);
	this->newScene({1}); 
	this->mVisualization.removeCirNode(this->mHeap[0]->id);

	this->newScene({1});
	this->mVisualization.highlightCirNode(this->mHeap[lastIndex]->id);

	this->newScene({2, 3});
	if (lastIndex & 1)
	{
		this->mVisualization.removeEdge(this->mHeap[parent(lastIndex)]->idEdgeLeft); 
		this->mHeap[parent(lastIndex)]->idEdgeLeft = 0; 
	}
	else {
		this->mVisualization.removeEdge(this->mHeap[parent(lastIndex)]->idEdgeRight); 
		this->mHeap[parent(lastIndex)]->idEdgeRight = 0;
	}
	this->mVisualization.moveCirNode(this->mHeap[lastIndex]->id, rootPos);
	this->mVisualization.setLabel(this->mHeap[lastIndex]->id, "1");

	this->mHeap[0]->value = this->mHeap[lastIndex]->value;
	this->mHeap[0]->id = this->mHeap[lastIndex]->id;
	this->mHeap.pop_back();

	this->downHeapAnimation(0);
}

Vector2 Algorithms::Heap::getPos(int i)
{
	return this->mVisualization.getCirNodePosition(this->mHeap[i]->id);
}

int Algorithms::Heap::parent(int i)
{
	return (i - 1) / 2;
}

int Algorithms::Heap::left(int i)
{
	return (2 * i + 1);
}

int Algorithms::Heap::right(int i)
{
	return (2 * i + 2);
}

void Algorithms::Heap::setMaxHeap()
{
	this->largerThan = [this](int a, int b) -> bool {
		return a > b;
	};
}

void Algorithms::Heap::setMinHeap()
{
	this->largerThan = [this](int a, int b) -> bool {
		return a < b;
	};
	this->isMaxHeap = false;
}
