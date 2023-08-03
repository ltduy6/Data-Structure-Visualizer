#include "AVL.h"
#include "../Helper/Helper.h"
#include "../Helper/GlobalVar.h"
#include <iostream>
#include <cmath>
#include <queue>
#include <algorithm>

Algorithms::AVL::AVL(Visualize::Visualization& visualization) : Algorithm(visualization)
{
}

Algorithms::AVL::~AVL()
{
}

void Algorithms::AVL::InitRandomFixSize(int size)
{
	std::vector<int> list;
	int i = 0; 
	while (i < size)
	{
		int rand = Helper::rand(0, 99);
		if (Helper::checkExist(list, rand) == false)
		{
			list.push_back(rand);
			i++;
		}
	}
	this->Init(list);
}

void Algorithms::AVL::Init(std::vector<int>& list)
{
	std::sort(list.begin(), list.end());
	this->sceneReset();
	if (list.size() == 0)
		return; 
	this->mRoot = this->SortedArrayToAVL(list, 0, list.size() - 1);
	this->mVisual = this->copyTree(this->mRoot);
	this->BalanceTree(this->mVisual);
}

void Algorithms::AVL::Insert(int value)
{
	this->sceneInit();
	this->mVisualization.addCode("insert v");										 // 0
	this->mVisualization.addCode("check balance factor of this and its children");   // 1
	this->mVisualization.addCode("    this.rotateRight");							 // 2
	this->mVisualization.addCode("    this.left.rotateLeft, this.rotateRight");      // 3
	this->mVisualization.addCode("    this.rotateLeft");							 // 4
	this->mVisualization.addCode("    this.right.rotateRight, this.rotateLeft");     // 5
	this->mVisualization.addCode("    this is balanced");                            // 6

	this->InitUntil(this->mRoot, this->mRoot, value, 0);
	this->newScene({});
	this->BalanceTree(this->mRoot);
	this->newScene({});
	this->mVisualization.resetColor();
	this->RotateUntil(this->mVisual, 0);
	this->newScene({6}); 
	this->mVisualization.resetColor();
}

void Algorithms::AVL::Remove(int value)
{
	this->sceneInit(); 

	this->mVisualization.addCode("remove v");										 // 0
	this->mVisualization.addCode("check balance factor of this and its children");   // 1
	this->mVisualization.addCode("    this.rotateRight");							 // 2
	this->mVisualization.addCode("    this.left.rotateLeft, this.rotateRight");      // 3
	this->mVisualization.addCode("    this.rotateLeft");							 // 4
	this->mVisualization.addCode("    this.right.rotateRight, this.rotateLeft");     // 5
	this->mVisualization.addCode("    this is balanced");                            // 6

	this->RemoveUntil(this->mRoot, value);
	this->finishRotation = true; 
	this->BalanceTree(this->mRoot);
	this->newScene({ 6 });
	this->mVisualization.resetColor();
}

void Algorithms::AVL::Search(int value)
{
	this->sceneInit(); 

	this->mVisualization.addCode("if this == null");					// 0
	this->mVisualization.addCode("	return null");						// 1
	this->mVisualization.addCode("else if this key == search value");	// 2
	this->mVisualization.addCode("	return this");						// 3
	this->mVisualization.addCode("else if this key < search value");    // 4
	this->mVisualization.addCode("	search right");						// 5
	this->mVisualization.addCode("else search left");					// 6

	searchValue(this->mRoot, value); 

	this->newScene({}); 
	this->mVisualization.resetColor();
}

void Algorithms::AVL::Update(int oldValue, int newValue)
{
	this->sceneInit();

	this->mVisualization.addCode("remove i");										 // 0
	this->mVisualization.addCode("check balance factor of this and its children");   // 1
	this->mVisualization.addCode("    this.rotateRight");							 // 2
	this->mVisualization.addCode("    this.left.rotateLeft, this.rotateRight");      // 3
	this->mVisualization.addCode("    this.rotateLeft");							 // 4
	this->mVisualization.addCode("    this.right.rotateRight, this.rotateLeft");     // 5
	this->mVisualization.addCode("    this is balanced");                            // 6

	this->RemoveUntil(this->mRoot, oldValue);
	this->finishRotation = true;
	this->BalanceTree(this->mRoot);
	this->newScene({ 6 });
	this->mVisualization.resetColor();

	this->mVisualization.addCode("insert newv");										 // 0
	this->mVisualization.addCode("check balance factor of this and its children");   // 1
	this->mVisualization.addCode("    this.rotateRight");							 // 2
	this->mVisualization.addCode("    this.left.rotateLeft, this.rotateRight");      // 3
	this->mVisualization.addCode("    this.rotateLeft");							 // 4
	this->mVisualization.addCode("    this.right.rotateRight, this.rotateLeft");     // 5
	this->mVisualization.addCode("    this is balanced");                            // 6

	this->InitUntil(this->mRoot, this->mRoot, newValue, 7);
	this->newScene({});
	this->BalanceTree(this->mRoot);
	this->newScene({});
	this->mVisualization.resetColor();
	this->RotateUntil(this->mVisual, 7);
	this->newScene({ 6 + 7});
	this->mVisualization.resetColor();
}

void Algorithms::AVL::sceneReset()
{
	this->mVisualization.reset();
	this->removeAVL(this->mRoot);
}

Algorithms::AVL::Node* Algorithms::AVL::InitUntil(Node*& root, Node*& parent, int value, int indexCode)
{
	if (root == nullptr)
	{
		root = new Node(); 
		root->value = value;
		root->id = this->mVisualization.createCirNode(value);
		std::cout << root->id << '\n';
		if (root != parent)
		{
			root->parent = parent; 
			if (parent)
			{
				if (parent->value < value)
				{
					parent->idEdgeRight = this->mVisualization.createEdge(
						this->mVisualization.getCirNodePosition(parent->id),
						this->mVisualization.getCirNodePosition(parent->id)
					);
					std::cout << parent->idEdgeRight << '\n';
					this->mVisualization.highlightEdge(parent->idEdgeRight);
				}
				else {
					parent->idEdgeLeft = this->mVisualization.createEdge(
						this->mVisualization.getCirNodePosition(parent->id),
						this->mVisualization.getCirNodePosition(parent->id)
					);
					std::cout << parent->idEdgeLeft << '\n';
					this->mVisualization.highlightEdge(parent->idEdgeLeft);
				}
			}
		}
		this->mVisualization.highlightCirNode(root->id);
		this->BalanceTree(this->mRoot);
		this->newScene({0 + indexCode});
		this->mVisualization.resetColor();
		this->finishRotation = true; 
		return root; 
	}
	
	this->newScene({0 + indexCode});
	this->mVisualization.highlightCirNode(root->id);

	this->newScene({0 + indexCode});
	this->mVisualization.unhighlightCirNode(root->id);

	if (root->value < value)
	{
		if (root->idEdgeRight)
		{
			this->newScene({0 + indexCode});
			this->mVisualization.highlightEdge(root->idEdgeRight);
		}
		root->right = this->InitUntil(root->right, root, value, indexCode);
	}
	else if (root->value > value)
	{
		if (root->idEdgeLeft)
		{
			this->newScene({0 + indexCode});
			this->mVisualization.highlightEdge(root->idEdgeLeft);
		}
		root->left = this->InitUntil(root->left, root, value, indexCode);
	}
	else {
		this->newScene({}); 
		this->mVisualization.resetColor(); 
		return root; 
	}

	int balanceFactor = Height(root->left) - Height(root->right);

	if (this->finishRotation)
	{
		newScene({1 + indexCode});
		this->mVisualization.highlightCirNode(root->id);
		this->mVisualization.setLabel(root->id, "bf = " + std::to_string(balanceFactor));
		newScene({1 + indexCode}); 
		this->mVisualization.setLabel(root->id, "");
	}

	if (balanceFactor < -1)
	{ 
		this->finishRotation = false; 
		if (value > root->right->value)
		{
			this->newScene({ 4 + indexCode});
			root = rotateLeft(root); 
		}
		else if (value < root->right->value)
		{
			this->newScene({ 5 + indexCode});
			root->right = rotateRight(root->right); 
			this->newScene({ 5 + indexCode});
			root = rotateLeft(root); 
		}
		this->mVisual = root; 
	}
	else if (balanceFactor > 1)
	{
		this->finishRotation = false; 
		if (value < root->left->value)
		{
			this->newScene({ 2 + indexCode});
			root = rotateRight(root); 
		}
		else if (value > root->left->value)
		{
			this->newScene({ 3 + indexCode});
			root->left = rotateLeft(root->left); 
			this->newScene({ 3 + indexCode});
			root = rotateRight(root);
		}
		this->mVisual = root;
	}

	this->mVisualization.resetColorCirNode(root->id);

	return root; 
}

Algorithms::AVL::Node* Algorithms::AVL::RemoveUntil(Node*& root, int value)
{
	if (root == nullptr)
		return root; 

	if (!this->helper)
	{
		this->newScene({0});
		this->mVisualization.highlightCirNode(root->id);
	}

	if (root->value != value && !this->helper)
	{
		this->newScene({0});
		this->mVisualization.unhighlightCirNode(root->id);
	}

	if (root->value > value)
	{
		if (root->idEdgeLeft)
		{
			this->newScene({0});
			this->mVisualization.highlightEdge(root->idEdgeLeft);
		}
		root->left = this->RemoveUntil(root->left, value);
		if (root->left)
			root->left->parent = root; 
	}
	else if (root->value < value)
	{
		if (root->idEdgeRight)
		{
			this->newScene({0});
			this->mVisualization.highlightEdge(root->idEdgeRight);
		}
		root->right = this->RemoveUntil(root->right, value);
		if (root->right)
			root->right->parent = root;
	}
	else {
		// Deletion 
		if (this->helper == false)
		{
			this->mVisualization.setLabel(root->id, "Remove"); 
		}
		this->newScene({ 0 });
		if (!root->left && !root->right)
		{
			if (this->helper)
			{
				this->mVisualization.highlightCirNode(root->id);
				this->mVisualization.updateCirNode(this->mVisual->id, this->mVisual->value);
			}
			
			if (root->parent)
			{
				bool isLeft = (root->value < root->parent->value); 
				int idEdge = (isLeft) ? (root->parent->idEdgeLeft) : (root->parent->idEdgeRight);
				this->mVisualization.removeEdge(idEdge);
				if (isLeft)
					root->parent->idEdgeLeft = 0;
				else
					root->parent->idEdgeRight = 0;
			}
			this->mVisualization.removeCirNode(root->id);
			delete root;
			root = nullptr;
		}
		else if (root->left && root->right)
		{
			Node* to_delete = root->right; 
			this->mVisualization.highlightEdge(root->idEdgeRight);
			
			this->helper = true;
			
			while (to_delete->left)
			{
				this->mVisualization.highlightCirNode(to_delete->id);
				this->newScene({});
				this->mVisualization.unhighlightCirNode(to_delete->id);
				this->mVisualization.highlightEdge(to_delete->idEdgeLeft);
				to_delete = to_delete->left;
			}

			this->mVisualization.highlightCirNode(to_delete->id);


			root->value = to_delete->value; 

			this->mVisual = root; 

			this->mVisualization.setLabel(root->id, "");

			root->right = RemoveUntil(root->right, to_delete->value);

			this->helper = false;

			if (root->right)
				root->right->parent = root;
		}
		else {
			Node* temp = (root->left) ? (root->left) : root->right; 

			this->mVisualization.removeEdge((root->left) ? (root->idEdgeLeft) : (root->idEdgeRight));
			this->mVisualization.removeCirNode(root->id);

			if(this->helper)
				this->mVisualization.updateCirNode(this->mVisual->id, this->mVisual->value);

			if (temp)
				temp->parent = root->parent;

			*root = *temp; 
			delete temp; 
		}
		this->BalanceTree(this->mRoot);
		this->newScene({});
		this->mVisualization.resetColor();
	}

	if (root == nullptr)
		return root; 

	printParent(root);

	// rotation 
	int balanceFactor = Height(root->left) - Height(root->right);

	if (this->finishRotation)
	{
		newScene({1});
		this->mVisualization.highlightCirNode(root->id);
		this->mVisualization.setLabel(root->id, "bf = " + std::to_string(balanceFactor));
		newScene({1});
		this->mVisualization.setLabel(root->id, "");
	}

	if (balanceFactor < -1)
	{
		this->finishRotation = false;
		if (this->getBalance(root->right) <= 0)
		{
			this->newScene({4});
			root = rotateLeft(root);
		}
		else
		{
			this->newScene({ 5 });
			root->right = rotateRight(root->right);
			this->newScene({ 5 });
			root = rotateLeft(root);
		}
	}
	else if (balanceFactor > 1)
	{
		this->finishRotation = false;
		if (this->getBalance(root->left) >= 0)
		{
			this->newScene({ 2 });
			root = rotateRight(root);
		}
		else
		{
			this->newScene({ 3 }); 
			root->left = rotateLeft(root->left);
			this->newScene({ 3 });
			root = rotateRight(root);
		}
	}
	this->mVisualization.resetColorCirNode(root->id);
	return root;
}

Algorithms::AVL::Node* Algorithms::AVL::SortedArrayToAVL(std::vector<int>& nums, int start, int end)
{
	if (start > end)
		return nullptr;

	int mid = (start + end) / 2; 
	Node* root = new Node(); 
	root->value = nums[mid]; 
	root->id = this->mVisualization.createCirNode(nums[mid]); 

	root->left = this->SortedArrayToAVL(nums, start, mid - 1); 
	root->right = this->SortedArrayToAVL(nums, mid + 1, end);

	if (root->left)
	{
		root->left->parent = root; 
		root->idEdgeLeft = this->mVisualization.createEdge(STARTING_POINT, STARTING_POINT);
	}
	if (root->right)
	{
		root->right->parent = root;
		root->idEdgeRight = this->mVisualization.createEdge(STARTING_POINT, STARTING_POINT);
	}
	return root; 
}

Algorithms::AVL::Node* Algorithms::AVL::rotateLeft(Node*& root)
{
	Node* right = root->right; 
	Node* right_left = right->left; 

	right->left = root; 
	root->right = right_left; 

	right->parent = root->parent; 
	root->parent = right; 

	if (right_left)
		right_left->parent = root; 

	this->mVisualization.removeEdge(root->idEdgeRight); 

	root->idEdgeRight = (right_left) ? this->mVisualization.createEdge(
		this->mVisualization.getCirNodePosition(root->id),
		this->mVisualization.getCirNodePosition(right_left->id)) : 0;
	

	this->mVisualization.removeEdge(right->idEdgeLeft); 

	right->idEdgeLeft = this->mVisualization.createEdge(
		this->mVisualization.getCirNodePosition(right->id),
		this->mVisualization.getCirNodePosition(root->id));

	

	bool isLeft = false; 

	if (right->parent)
	{
		if (right->parent->value > right->value)
		{
			isLeft = true; 
		}
		this->mVisualization.removeEdge((isLeft) ? right->parent->idEdgeLeft : right->parent->idEdgeRight); 
		if (isLeft)
		{
			right->parent->idEdgeLeft = this->mVisualization.createEdge(
				this->mVisualization.getCirNodePosition(right->parent->id),
				this->mVisualization.getCirNodePosition(right->id));
		}
		else {
			right->parent->idEdgeRight = this->mVisualization.createEdge(
				this->mVisualization.getCirNodePosition(right->parent->id),
				this->mVisualization.getCirNodePosition(right->id)
			);
		}
	}


	if (root->right)
	{
		this->mVisualization.highlightEdge(root->idEdgeRight);
		this->mVisualization.moveEdgeDes(root->idEdgeRight, this->mVisualization.getCirNodePosition(root->right->id)); 
	}

	
	if (right->idEdgeLeft)
	{
		this->mVisualization.highlightEdge(right->idEdgeLeft);
		this->mVisualization.moveEdgeDes(right->idEdgeLeft, this->mVisualization.getCirNodePosition(root->id));
	}

	
	if (right->parent)
	{
		this->mVisualization.highlightEdge((isLeft) ? right->parent->idEdgeLeft : right->parent->idEdgeRight);
		this->mVisualization.moveEdgeDes((isLeft) ? right->parent->idEdgeLeft : right->parent->idEdgeRight, 
			this->mVisualization.getCirNodePosition(right->id)); 
	}

	return root = right; 
}

Algorithms::AVL::Node* Algorithms::AVL::rotateRight(Node*& root)
{
	Node* left = root->left; 
	Node* left_right = left->right; 

	left->right = root; 
	root->left = left_right; 

	left->parent = root->parent; 
	root->parent = left; 

	if (left_right)
		left_right->parent = root; 

	this->mVisualization.removeEdge(root->idEdgeLeft); 

	root->idEdgeLeft = (left_right) ? this->mVisualization.createEdge(
		this->mVisualization.getCirNodePosition(root->id),
		this->mVisualization.getCirNodePosition(left_right->id)) : 0;

	this->mVisualization.removeEdge(left->idEdgeRight); 

	left->idEdgeRight = this->mVisualization.createEdge(
		this->mVisualization.getCirNodePosition(left->id),
		this->mVisualization.getCirNodePosition(root->id)
	);

	bool isLeft = false; 
	if (left->parent)
	{
		if (left->parent->value > left->value)
			isLeft = true; 
		this->mVisualization.removeEdge((isLeft) ? left->parent->idEdgeLeft : left->parent->idEdgeRight); 
		if (isLeft)
		{
			left->parent->idEdgeLeft = this->mVisualization.createEdge(
				this->mVisualization.getCirNodePosition(left->parent->id),
				this->mVisualization.getCirNodePosition(left->id)
			); 
		}
		else {
			left->parent->idEdgeRight = this->mVisualization.createEdge(
				this->mVisualization.getCirNodePosition(left->parent->id),
				this->mVisualization.getCirNodePosition(left->id)
			);
		}
	}

	
	if (left_right)
	{
		this->mVisualization.highlightEdge(root->idEdgeLeft);
		this->mVisualization.moveEdgeDes(root->idEdgeLeft, this->mVisualization.getCirNodePosition(left_right->id));
	}

	

	if (left->idEdgeRight)
	{
		this->mVisualization.highlightEdge(left->idEdgeRight);
		this->mVisualization.moveEdgeDes(left->idEdgeRight, this->mVisualization.getCirNodePosition(root->id));
	}

	
	if (left->parent)
	{
		this->mVisualization.highlightEdge((isLeft) ? left->parent->idEdgeLeft : left->parent->idEdgeRight);
		this->mVisualization.moveEdgeDes((isLeft) ? left->parent->idEdgeLeft : left->parent->idEdgeRight,
			this->mVisualization.getCirNodePosition(left->id)); 
	}

	return root = left; 
}

void Algorithms::AVL::searchValue(Node* root, int value)
{
	if (root == nullptr)
	{
		this->newScene({ 0, 1 });
		return;
	}

	this->newScene({}); 
	this->mVisualization.highlightCirNode(root->id); 

	if (root->value == value)
	{
		this->newScene({3});
		this->mVisualization.setLabel(root->id, "v");
		this->newScene({3}); 
		this->mVisualization.setLabel(root->id, "");
		return;
	}

	this->newScene({ 2 });

	if (root->value < value)
	{
		this->newScene({4});
		this->mVisualization.unhighlightCirNode(root->id);
		if (root->idEdgeRight)
		{
			this->newScene({ 5 });
			this->mVisualization.highlightEdge(root->idEdgeRight);
		}
		searchValue(root->right, value); 
	}
	else
	{
		this->newScene({6});
		this->mVisualization.unhighlightCirNode(root->id);
		if (root->idEdgeLeft)
			this->mVisualization.highlightEdge(root->idEdgeLeft);
		searchValue(root->left, value);
	}
}

Algorithms::AVL::Node* Algorithms::AVL::copyTree(Node* root)
{
	if (root == nullptr)
		return nullptr; 

	Node* newNode = new Node(); 
	newNode->value = root->value; 
	newNode->id = root->id; 
	newNode->idEdgeLeft = root->idEdgeLeft; 
	newNode->idEdgeRight = root->idEdgeRight; 

	newNode->left = this->copyTree(root->left); 
	if (newNode->left)
		newNode->left->parent = newNode; 
	newNode->right = this->copyTree(root->right); 
	if (newNode->right)
		newNode->right->parent = newNode;

	return newNode; 
}

void Algorithms::AVL::printParent(Node* root)
{
	if (root == nullptr)
		return;

	printParent(root->left); 
	if (root->parent)
		std::cout << root->value << ' ' << root->parent->value << '\n';
	printParent(root->right);
}

void Algorithms::AVL::removeAVL(Node*& root)
{
	if (root == nullptr)
		return;
	removeAVL(root->right); 
	removeAVL(root->left); 
	
	delete root; 
	root = nullptr;
}

void Algorithms::AVL::printBST(Node* root)
{
	if (root == nullptr)
		return; 
	printBST(root->left); 
	std::cout << root->value << ' '; 
	printBST(root->right);
}

void Algorithms::AVL::RotateUntil(Node*& root, int indexCode)
{
	while (root)
	{
		this->newScene({1 + indexCode}); 
		this->mVisualization.highlightCirNode(root->id); 
		this->mVisualization.setLabel(root->id, "bf = " + std::to_string(this->getBalance(root)));
		this->newScene({1 + indexCode}); 
		this->mVisualization.unhighlightCirNode(root->id);
		this->mVisualization.setLabel(root->id, "");
		root = root->parent;
	}
}

void Algorithms::AVL::traverse(Node*& root, Vector2 pos, int level, int& count)
{
	if (root == nullptr)
		return;

	traverse(root->left, Vector2{ pos.x, pos.y + VERTICAL_SPACE }, level + 1, count);

	while (pos.x + 2 * (count + MODIFIER) * HORIZONTAL_SPACE - RADIUS < 0)
		MODIFIER++;
	while (pos.x + 2 * (count + MODIFIER) * HORIZONTAL_SPACE - RADIUS > Constant::WINDOW_WIDTH)
		MODIFIER--;

	this->mVisualization.moveCirNode(root->id, Vector2{pos.x + 2 * (count + MODIFIER) * HORIZONTAL_SPACE, pos.y});
	count++;

	traverse(root->right, Vector2{ pos.x, pos.y + VERTICAL_SPACE }, level + 1, count);
}

void Algorithms::AVL::modifyDistance(Node*& root)
{
	int numNode = this->countNode(root);
	if (numNode < 20)
		this->HORIZONTAL_SPACE = 50;
	else if (numNode <= 30)
		this->HORIZONTAL_SPACE = 30;
	else if (numNode <= 50)
		this->HORIZONTAL_SPACE = 20;

	int height = this->Height(root); 
	if (height < 10)
		this->VERTICAL_SPACE = 100;
	else if (height <= 20)
		this->VERTICAL_SPACE = 60;
	else if (height <= 50)
		this->VERTICAL_SPACE = 30;
}

void Algorithms::AVL::BalanceTree(Node*& root)
{
	this->modifyDistance(root); 
	Vector2 pos = Vector2{ STARTING_POINT.x - HORIZONTAL_SPACE * this->countNode(root), STARTING_POINT.y };
	int count = 0;
	this->traverse(root, pos, 1, count);
	this->addEdge(root);
}

void Algorithms::AVL::addEdge(Node*& root)
{
	if (root == nullptr)
		return; 
	std::queue<Node*> q; 
	q.push(root); 
	while (!q.empty())
	{
		Node* curr = q.front(); 
		q.pop(); 
		if (curr->left)
		{
			if (curr->idEdgeLeft != 0)
			{
				this->mVisualization.moveEdgeSource(curr->idEdgeLeft, this->mVisualization.getCirNodePosition(curr->id));
				this->mVisualization.moveEdgeDes(curr->idEdgeLeft, this->mVisualization.getCirNodePosition(curr->left->id));
			}
			else {
				curr->idEdgeLeft = this->mVisualization.createEdge(this->mVisualization.getCirNodePosition(curr->id),
					this->mVisualization.getCirNodePosition(curr->left->id));
			}
			q.push(curr->left);
		}
		if (curr->right)
		{
			if (curr->idEdgeRight != 0)
			{
				this->mVisualization.moveEdgeSource(curr->idEdgeRight, this->mVisualization.getCirNodePosition(curr->id));
				this->mVisualization.moveEdgeDes(curr->idEdgeRight, this->mVisualization.getCirNodePosition(curr->right->id));
			}
			else {
				curr->idEdgeRight = this->mVisualization.createEdge(this->mVisualization.getCirNodePosition(curr->id),
					this->mVisualization.getCirNodePosition(curr->right->id));
			}
			q.push(curr->right);
		}
	}
}


int Algorithms::AVL::Height(Node* root)
{
	if (root == nullptr)
		return 0; 
	return std::max(Height(root->left), Height(root->right)) + 1; 
}

int Algorithms::AVL::Width(Node* root)
{
	if (root == nullptr)
		return 0; 
	int width = 1; 
	std::queue<Node*> q; 
	q.push(root); 
	while (!q.empty())
	{
		int levelSize = q.size(); 

		while (levelSize--)
		{
			Node* curr = q.front();
			q.pop();

			if (curr->left)
				q.push(curr->left); 
			if (curr->right)
				q.push(curr->right);
		}
		width = std::max(width, (int)q.size()); 
	}
	return width; 
}

int Algorithms::AVL::countNode(Node* root)
{
	if (root == nullptr)
		return 0; 
	return countNode(root->left) + countNode(root->right) + 1;
}

int Algorithms::AVL::getBalance(Node* root)
{
	return Height(root->left) - Height(root->right); 
}
