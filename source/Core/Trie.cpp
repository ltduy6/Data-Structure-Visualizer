#include "Trie.h"
#include <iostream>

Algorithms::Trie::Trie(Visualize::Visualization& visualization) : Algorithm(visualization)
{
	this->mRoot = new Node(' ');
	this->mRoot->id = this->mVisualization.createCharNode(" ");
	this->mVisualization.moveCirNode(this->mRoot->id, STARTING_POINT);
}

Algorithms::Trie::~Trie()
{
}

void Algorithms::Trie::InitRandomFixSize(int size)
{
	std::vector<std::string> list = readFromFileRange<std::string>("Test/Word.txt", size); 
	this->Init(list);
}

void Algorithms::Trie::Init(std::vector<std::string>& list)
{
	for (std::string value : list)
		this->insertAnimation(value, false);
}

void Algorithms::Trie::Insert(std::string value)
{
	this->sceneInit();
	this->insertAnimation(value);
}

void Algorithms::Trie::Remove(std::string value)
{
	this->sceneInit();
	this->deleteWordAnimation(this->mRoot, value);
	this->balanceTree();
}

bool Algorithms::Trie::Search(std::string value)
{
	this->sceneInit(); 
	Node* res = this->searchAnimation(value);
	if (res && res->isEndOfWord == true)
	{
		this->newScene({}); 
		this->mVisualization.setLabel(res->id, value);
		this->newScene({}); 
		this->mVisualization.highlightCirNode(res->id);
		this->mVisualization.setLabel(res->id, "");
		return true; 
	}
	else if (res)
	{
		this->newScene({});
		this->mVisualization.resetColorCirNode(res->id);
	}
	return false;
}

void Algorithms::Trie::sceneReset()
{
	this->mVisualization.reset(); 
	this->deleteTrie(this->mRoot);
}

Vector2 Algorithms::Trie::getPos(int id)
{
	return this->mVisualization.getCirNodePosition(id);
}

void Algorithms::Trie::balanceTree()
{
	Vector2 bound = { 200, 50 };
	this->modifyDistance();
	this->setNodePos(this->mRoot, bound);
	this->setEdgePos(this->mRoot);
}

void Algorithms::Trie::setNodePos(Node* root, Vector2& pos)
{
	if (!root)
		return; 
	int cntChild = root->children.size(); 
	int i = 0; 
	for (const auto& child : root->children)
	{
		if (i < (cntChild + 1) / 2)
		{
			pos.y += VERTICAL_SPACE;
			setNodePos(child.second, pos);
			pos.y -= VERTICAL_SPACE;
			if (child.second)
			{
				lastChild = child.second;
			}
		}
		i++;
	}
	if (cntChild == 1)
	{
		Vector2 _pos = this->getPos(lastChild->id); 
		_pos.y -= VERTICAL_SPACE; 
		this->mVisualization.moveCirNode(root->id, _pos);
	}
	else {
		this->mVisualization.moveCirNode(root->id, pos); 
		pos.x += HORIZONTAL_SPACE + ELEMENT_SIZE / 2 + 10; 
	}

	i = 0;

	for (const auto& child : root->children)
	{
		if (i < cntChild && i >= (cntChild + 1) / 2)
		{
			pos.y += VERTICAL_SPACE;
			setNodePos(child.second, pos);
			pos.y -= VERTICAL_SPACE;
		}
		i++;
	}
}


void Algorithms::Trie::setEdgePos(Node* root)
{
	if (!root)
		return; 
	for (const auto& child : root->children)
	{
		if (root->Edge[child.first])
		{
			this->mVisualization.moveEdgeSource(root->Edge[child.first], this->getPos(root->id)); 
			this->mVisualization.moveEdgeDes(root->Edge[child.first], this->getPos(child.second->id));
		}
		setEdgePos(child.second);
	}
}

void Algorithms::Trie::modifyDistance()
{
	if (maxLength < 12)
		this->VERTICAL_SPACE = 100;
	else if (maxLength < 15)
		this->VERTICAL_SPACE = 80;
	else
		this->VERTICAL_SPACE = 70;

	int currentSize = this->mRoot->children.size(); 
	if (currentSize < 5)
		this->HORIZONTAL_SPACE = 50;
	else if (currentSize <= 10)
		this->HORIZONTAL_SPACE = 40;
	else
		this->HORIZONTAL_SPACE = 30;
	
	int numNode = this->countNode(mRoot);
	if (numNode < 30)
		this->HORIZONTAL_SPACE = 50;
	else if (numNode <= 40)
		this->HORIZONTAL_SPACE = 40;
	else
		this->HORIZONTAL_SPACE = 30;
}

void Algorithms::Trie::insertAnimation(const std::string& word, bool animation)
{
	int length = word.length(); 
	this->maxLength = std::max(this->maxLength, length);

	Node* curr = this->mRoot; 
	for (char c : word)
	{
		if (curr->children.find(c) == curr->children.end())
		{
			if (animation)
				this->newScene({});
			Node* newNode = new Node(c); 
			newNode->id = this->mVisualization.createCharNode(newNode->value);
			if(animation)
				this->mVisualization.unhighlightCirNode(newNode->id);
			curr->children.emplace(c, newNode);

			this->balanceTree();
			if (curr->isEndOfWord == false && curr != this->mRoot && animation)
			{
				this->mVisualization.resetColorCirNode(curr->id);
			}
			if(animation)
				this->newScene({}); 
			curr->Edge[c] = this->mVisualization.createEdge(this->getPos(curr->id), this->getPos(newNode->id));
		}
		else if(animation)
		{
			this->newScene({});
			this->mVisualization.resetColorCirNode(curr->id); 
			this->mVisualization.unhighlightCirNode(curr->children[c]->id);
		}
		curr = curr->children[c];
	}
	curr->isEndOfWord = true;	
	this->mVisualization.highlightCirNode(curr->id);
}

void Algorithms::Trie::deleteWordAnimation(Node* node, const std::string& word, int depth)
{
	if (!node)
		return; 
	if (depth == word.length())
	{
		if (node->isEndOfWord)
		{
			node->isEndOfWord = false;
			this->newScene({}); 
			this->mVisualization.resetColorCirNode(node->id);
		}
		return;
	}
	char currChar = word[depth]; 
	auto it = node->children.find(currChar); 
	if (it != node->children.end())
	{
		Node* nextNode = it->second; 
		if (!node->isEndOfWord)
		{
			this->newScene({});
			this->mVisualization.resetColorCirNode(node->id);
		}
		if (!nextNode->isEndOfWord)
		{
			this->mVisualization.unhighlightCirNode(nextNode->id);
		}

		deleteWordAnimation(nextNode, word, depth + 1); 

		if (!nextNode->isEndOfWord && nextNode->children.empty() && node != this->mRoot)
		{
			this->newScene({});
			this->mVisualization.removeCirNode(nextNode->id); 
			this->mVisualization.removeEdge(node->Edge[currChar]);

			node->children.erase(currChar); 
			node->Edge.erase(currChar);
			delete nextNode;

			if (!node->isEndOfWord)
			{
				this->newScene({});
				this->mVisualization.unhighlightCirNode(node->id);
			}
		}
		else if (node == this->mRoot)
		{
			if (nextNode->children.empty())
			{
				this->newScene({}); 
				this->mVisualization.removeCirNode(nextNode->id);
				this->mVisualization.removeEdge(node->Edge[currChar]);

				node->children.erase(currChar);
				node->Edge.erase(currChar);
				delete nextNode;
			}
			else {
				this->mVisualization.resetColorCirNode(nextNode->id);
			}
		}
	}
}

Algorithms::Trie::Node* Algorithms::Trie::searchAnimation(const std::string& word)
{
	Node* curr = this->mRoot; 
	for (char c : word)
	{
		auto it = curr->children.find(c); 
		if (it == curr->children.end())
			return nullptr; 
		this->newScene({}); 
		this->mVisualization.resetColorCirNode(curr->id); 
		this->mVisualization.unhighlightCirNode(it->second->id);
		curr = it->second; 
	}
	return curr; 
}

void Algorithms::Trie::deleteTrie(Node* root)
{
	if (!root)
		return; 
	for (const auto& child : root->children)
		deleteTrie(child.second);
	delete root;
}

int Algorithms::Trie::countNode(Node* root)
{
	if (root == nullptr)
		return 0; 
	int s = 0; 
	for (const auto& child : root->children)
	{
		s += countNode(child.second);
	}

	return s + 1;
}
