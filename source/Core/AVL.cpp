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
	std::sort(list.begin(), list.end());
	this->Init(list);
}

void Algorithms::AVL::Init(std::vector<int>& list)
{
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
	this->InitUntil(this->mRoot, this->mRoot, value);
	this->BalanceTree(this->mRoot);
	this->newScene({}); 
	this->mVisualization.resetColor();
}

void Algorithms::AVL::sceneReset()
{
	this->mVisualization.reset();
	this->mRoot = nullptr; 
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::InitUntil(Node::Ptr& root, Node::Ptr& parent, int value)
{
	if (root == nullptr)
	{
		root = std::make_shared<Node>(); 
		root->value = value;
		root->id = this->mVisualization.createCirNode(value);
		std::cout << root->id << '\n';
		root->height = 1; 
		if (root != parent)
		{
			root->parent = parent; 
			if (parent)
			{
				if (parent->value < value)
				{
					parent->idEdgeRight = this->mVisualization.createEdge(
						this->mVisualization.getCirNodePosition(parent->id),
						this->mVisualization.getCirNodePosition(root->id)
					);
					root->idEdge = parent->idEdgeRight;
					this->mVisualization.highlightEdge(parent->idEdgeRight);
				}
				else {
					parent->idEdgeLeft = this->mVisualization.createEdge(
						this->mVisualization.getCirNodePosition(parent->id),
						this->mVisualization.getCirNodePosition(root->id)
					);
					root->idEdge = parent->idEdgeLeft;
					this->mVisualization.highlightEdge(parent->idEdgeLeft);
				}
				std::cout << parent->value << '\n';
			}
		}
		this->mVisualization.highlightCirNode(root->id);
		this->BalanceTree(this->mRoot);
		this->newScene({});
		this->mVisualization.resetColor();
		this->finishRotation = true; 
		return root; 
	}
	
	this->newScene({});
	this->mVisualization.highlightCirNode(root->id);

	this->newScene({}); 
	this->mVisualization.unhighlightCirNode(root->id); 

	if (root->value < value)
	{
		if (root->idEdgeRight)
		{
			this->newScene({});
			this->mVisualization.highlightEdge(root->idEdgeRight);
		}
		this->InitUntil(root->right, root, value);
	}
	else if (root->value > value)
	{
		if (root->idEdgeLeft)
		{
			this->newScene({});
			this->mVisualization.highlightEdge(root->idEdgeLeft);
		}
		this->InitUntil(root->left, root, value);
	}
	else {
		this->newScene({}); 
		this->mVisualization.resetColor(); 
		return root; 
	}

	int balanceFactor = Height(root->right) - Height(root->left);

	Node::Ptr target = this->searchValue(this->mVisual, root->value); 

	if (this->finishRotation)
	{
		newScene({});
		this->mVisualization.highlightCirNode(root->id);
	}

	if (balanceFactor > 1)
	{
		finishRotation = false; 
		if (value > root->right->value)
		{
			root = rotateLeft(root); 
		}
		else if (value < root->right->value)
		{
			root->right = rotateRight(root->right); 
			root = rotateLeft(root); 
		}
	}
	else if (balanceFactor < -1)
	{
		finishRotation = false; 
		if (value < root->left->value)
			root = rotateRight(root); 
		else if (value > root->left->value)
		{
			root->left = rotateLeft(root->left); 
			root = rotateRight(root);
		}
	}

	newScene({});
	this->mVisualization.resetColorCirNode(root->id);

	return root; 
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::SortedArrayToAVL(std::vector<int>& nums, int start, int end)
{
	if (start > end)
		return nullptr;

	int mid = (start + end) / 2; 
	Node::Ptr root = std::make_shared<Node>(); 
	root->value = nums[mid]; 
	root->id = this->mVisualization.createCirNode(nums[mid]); 

	root->left = this->SortedArrayToAVL(nums, start, mid - 1); 
	root->right = this->SortedArrayToAVL(nums, mid + 1, end);

	return root; 
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::rotateLeft(Node::Ptr& root)
{
	this->newScene({}); 
	Node::Ptr right = root->right; 
	Node::Ptr right_left = right->left; 


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
	
	/*this->newScene({});*/
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

Algorithms::AVL::Node::Ptr Algorithms::AVL::rotateRight(Node::Ptr& root)
{
	this->newScene({});
	Node::Ptr left = root->left; 
	Node::Ptr left_right = left->right; 

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

	
	/*this->newScene({});*/
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

Algorithms::AVL::Node::Ptr Algorithms::AVL::searchValue(Node::Ptr root, int value)
{
	if (root == nullptr || root->value == value)
		return root; 
	if (root->value < value)
		return searchValue(root->right, value); 
	else
		return searchValue(root->left, value);
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::copyTree(Node::Ptr root)
{
	if (root == nullptr)
		return nullptr; 

	Node::Ptr newNode = std::make_shared<Node>(); 
	newNode->value = root->value; 
	newNode->id = root->id; 
	newNode->idEdgeLeft = root->idEdgeLeft; 
	newNode->idEdgeRight = root->idEdgeRight; 
	newNode->parent = root->parent; 

	newNode->left = this->copyTree(root->left); 
	newNode->right = this->copyTree(root->right); 

	return newNode; 
}

void Algorithms::AVL::traverse(Node::Ptr& root, Vector2 pos, int level, int& count)
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

void Algorithms::AVL::modifyDistance(Node::Ptr& root)
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

void Algorithms::AVL::BalanceTree(Node::Ptr& root)
{
	this->modifyDistance(root); 
	Vector2 pos = Vector2{ STARTING_POINT.x - HORIZONTAL_SPACE * this->countNode(root), STARTING_POINT.y };
	int count = 0;
	this->traverse(root, pos, 1, count);
	this->addEdge(root);
}

void Algorithms::AVL::addEdge(Node::Ptr& root)
{
	if (root == nullptr)
		return; 
	std::queue<Node::Ptr> q; 
	q.push(root); 
	while (!q.empty())
	{
		Node::Ptr curr = q.front(); 
		q.pop(); 
		if (curr->idEdge != 0)
		{
			this->mVisualization.moveEdgeSource(curr->idEdge, this->mVisualization.getCirNodePosition(curr->parent->id));
			this->mVisualization.moveEdgeDes(curr->idEdge, this->mVisualization.getCirNodePosition(curr->id));
		}
		else if (curr->parent != nullptr)
		{
			curr->idEdge = this->mVisualization.createEdge(this->mVisualization.getCirNodePosition(curr->parent->id),
				this->mVisualization.getCirNodePosition(curr->id));
		}
		if (curr->left)
		{
			/*if (curr->idEdgeLeft != 0)
			{
				this->mVisualization.moveEdgeSource(curr->idEdgeLeft, this->mVisualization.getCirNodePosition(curr->id));
				this->mVisualization.moveEdgeDes(curr->idEdgeLeft, this->mVisualization.getCirNodePosition(curr->left->id));
			}
			else {
				curr->idEdgeLeft = this->mVisualization.createEdge(this->mVisualization.getCirNodePosition(curr->id),
					this->mVisualization.getCirNodePosition(curr->left->id));
			}*/
			q.push(curr->left);
		}
		if (curr->right)
		{
			/*if (curr->idEdgeRight != 0)
			{
				this->mVisualization.moveEdgeSource(curr->idEdgeRight, this->mVisualization.getCirNodePosition(curr->id));
				this->mVisualization.moveEdgeDes(curr->idEdgeRight, this->mVisualization.getCirNodePosition(curr->right->id));
			}
			else {
				curr->idEdgeRight = this->mVisualization.createEdge(this->mVisualization.getCirNodePosition(curr->id),
					this->mVisualization.getCirNodePosition(curr->right->id));
			}*/
			q.push(curr->right);
		}
	}
}

int Algorithms::AVL::Height(Node::Ptr root)
{
	if (root == nullptr)
		return 0; 
	return std::max(Height(root->left), Height(root->right)) + 1; 
}

int Algorithms::AVL::Width(Node::Ptr root)
{
	if (root == nullptr)
		return 0; 
	int width = 1; 
	std::queue<Node::Ptr> q; 
	q.push(root); 
	while (!q.empty())
	{
		int levelSize = q.size(); 

		while (levelSize--)
		{
			Node::Ptr curr = q.front();
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

int Algorithms::AVL::countNode(Node::Ptr root)
{
	if (root == nullptr)
		return 0; 
	return countNode(root->left) + countNode(root->right) + 1;
}

int Algorithms::AVL::getBalance(Node::Ptr root)
{
	return Height(root->right) - Height(root->left); 
}
