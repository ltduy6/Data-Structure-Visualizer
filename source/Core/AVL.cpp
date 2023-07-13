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
	if (list.size() == 0)
		return; 
	this->sceneReset();
	this->mRoot = this->SortedArrayToAVL(list, 0, list.size() - 1);
	this->modifyDistance();
	this->BalanceTree();
}

void Algorithms::AVL::Insert(int value)
{
	this->newScene({});
	this->InitUntil(this->mRoot, value);
	this->modifyDistance(); 
	this->BalanceTree(); 
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::InitUntil(Node::Ptr& root, int value)
{
	if (root == nullptr)
	{
		root = std::make_shared<Node>(); 
		root->value = value;
		root->id = this->mVisualization.createCirNode(value);
		root->height = 1; 
		return root; 
	}
	
	if (root->value < value)
	{
		root->right =  this->InitUntil(root->right, value);
	}
	else if (root->value > value)
	{
		root->left =  this->InitUntil(root->left, value);
	}

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

Algorithms::AVL::Node::Ptr Algorithms::AVL::rotateLeft(Node::Ptr root)
{
	Node::Ptr right = root->right; 
	Node::Ptr right_left = right->left; 

	right->left = root; 
	root->right = right_left; 

	return right; 
}

Algorithms::AVL::Node::Ptr Algorithms::AVL::rotateRight(Node::Ptr root)
{
	Node::Ptr left = root->left; 
	Node::Ptr left_right = left->right; 

	left->right = root; 
	root->left = left_right; 

	return left; 
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

void Algorithms::AVL::modifyDistance()
{
	int numNode = this->countNode(this->mRoot);
	if (numNode < 20)
		this->HORIZONTAL_SPACE = 50;
	else if (numNode <= 30)
		this->HORIZONTAL_SPACE = 30;
	else if (numNode <= 50)
		this->HORIZONTAL_SPACE = 20;

	int height = this->Height(this->mRoot); 
	if (height < 10)
		this->VERTICAL_SPACE = 100;
	else if (height <= 20)
		this->VERTICAL_SPACE = 60;
	else if (height <= 50)
		this->VERTICAL_SPACE = 30;
}

void Algorithms::AVL::BalanceTree()
{
	Vector2 pos = Vector2{ STARTING_POINT.x - HORIZONTAL_SPACE * this->countNode(this->mRoot), STARTING_POINT.y };
	int count = 0;
	this->traverse(this->mRoot, pos, 1, count);
	this->addEdge();
}

void Algorithms::AVL::addEdge()
{
	if (this->mRoot == nullptr)
		return; 
	std::queue<Node::Ptr> q; 
	q.push(this->mRoot); 
	while (!q.empty())
	{
		Node::Ptr curr = q.front(); 
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
