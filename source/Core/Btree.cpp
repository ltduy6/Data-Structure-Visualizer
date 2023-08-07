#include "Btree.h"
#include <iostream>
#include <queue>

typedef char BTREE_EXCEPTION;

#define NEW_ROOT 2
#define MODIFIED_NOT_ROOT 1
#define NOT_MODIFIED 0

#define NULL 0
#define SEARCH_KEY_NOT_FOUND 's'
#define REMOVE_KEY_NOT_FOUND 'r'

Algorithms::Btree::Btree(Visualize::Visualization& visualization) : Algorithm(visualization)
{
}

Algorithms::Btree::~Btree()
{
}

void Algorithms::Btree::InitRandomFixSize(int size)
{
	if (size == 0)
	{
		this->sceneReset();
		return;
	}
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

void Algorithms::Btree::Init(std::vector<int>& list)
{
	this->sceneReset();
	for (int value : list)
		this->insertNonAni(value);
}

void Algorithms::Btree::Insert(int value)
{
	this->sceneInit();
	this->mVisualization.addCode("if this is leaf"); 
	this->mVisualization.addCode("	insert v");			
	this->mVisualization.addCode("if this is full"); 
	this->mVisualization.addCode("	split this");
	std::vector<int> line = { 0, 1, 2, 3 };

	this->insertAnimation(value, line);
	this->newScene({}); 
	this->mVisualization.resetColor();
}

void Algorithms::Btree::Remove(int value)
{
	if (this->mRoot == nullptr || this->checkExist(value) == false)
		return;
	this->sceneInit();
	this->mVisualization.addCode("Find v");
	this->mVisualization.addCode("If v is in this and this is a leaf"); 
	this->mVisualization.addCode("	remove v"); 
	this->mVisualization.addCode("If v is in this and this is an internal node"); 
	this->mVisualization.addCode("	replace v by its predecessor");
	this->mVisualization.addCode("	replace v by its successor");
	this->mVisualization.addCode("	merge children");
	this->mVisualization.addCode("Fix size of this");

	std::vector<int> line = { 0, 1, 2, 3, 4, 5, 6, 7};
	this->removeAnimation(value, line);
	this->balanceTree(this->mRoot);
	this->newScene({});
	this->mVisualization.resetColor();
}

void Algorithms::Btree::Search(int value)
{
	if (this->mRoot == nullptr)
		return;
	this->sceneInit();
	this->mVisualization.addCode("If v is in this"); 
	this->mVisualization.addCode("	return v");
	this->mVisualization.addCode("else if this is leaf");
	this->mVisualization.addCode("	return null");
	this->mVisualization.addCode("else search child");
	this->search(value); 
	this->newScene({});
	this->mVisualization.resetColor();
}

void Algorithms::Btree::Update(int oldValue, int newValue)
{
	this->sceneInit();
	// Remove i
	this->mVisualization.addCode("Find i");
	this->mVisualization.addCode("If v is in this and this is a leaf");
	this->mVisualization.addCode("	remove i");
	this->mVisualization.addCode("If i is in this and this is an internal node");
	this->mVisualization.addCode("	replace i by its predecessor");
	this->mVisualization.addCode("	replace i by its successor");
	this->mVisualization.addCode("	merge children");
	this->mVisualization.addCode("Fix size of this");

	// Insert newv
	this->mVisualization.addCode("if this is leaf");
	this->mVisualization.addCode("	insert newv");
	this->mVisualization.addCode("if this is full");
	this->mVisualization.addCode("	split this");

	std::vector<int> lineRemove = {0, 1, 2, 3, 4, 5, 6, 7};
	std::vector<int> lineInsert = { 8, 9, 10, 11 };

	this->removeAnimation(oldValue, lineRemove); 
	this->balanceTree(this->mRoot);
	this->newScene({});
	this->mVisualization.resetColor();
	this->insertAnimation(newValue, lineInsert);
	this->newScene({});
	this->mVisualization.resetColor();
}

void Algorithms::Btree::sceneReset()
{
	this->mVisualization.reset(); 
	this->freeNode(this->mRoot);
	this->mRoot = nullptr;
}

void Algorithms::Btree::insertNonAni(int k)
{
	if (this->mRoot == nullptr)
	{
		this->mRoot = new BtreeNode();
		this->initializeNode(this->mRoot);
		this->mRoot->key[0] = k;
		this->mRoot->size = 1;
		this->mRoot->id = this->mVisualization.createBlock({ k });
		this->balanceTree(this->mRoot);
		return;
	}

	if (mRoot->size == 2 * minDegree - 1)
	{
		BtreeNode* newRoot = new BtreeNode();
		this->initializeNode(newRoot);
		newRoot->id = this->mVisualization.createBlock({});
		this->mVisualization.moveBlock(newRoot->id, this->mVisualization.getBlockPos(this->mRoot->id, 0) - Vector2{ 0, 2 * HEIGHT });
		newRoot->leaf = false;
		newRoot->child[0] = mRoot;
		splitChild(newRoot, 0);
		newRoot->idEdge[0] = this->mVisualization.createEdgeOffSet(
			this->mVisualization.getBlockPos(newRoot->id, 0), this->mVisualization.getBlockMid(mRoot->id)
		);
		mRoot = newRoot;
		this->balanceTree(this->mRoot);
	}
	BtreeNode* curr = mRoot;
	while (!curr->leaf)
	{

		int index = curr->size - 1;
		while (index >= 0 && k < curr->key[index])
			index--;
		index++;

		if (curr->child[index]->size == 2 * minDegree - 1)
		{
			splitChild(curr, index);
			this->createEdge(this->mRoot);
			if (curr->key[index] < k)
				index++;
		}
		curr = curr->child[index];
	}

	nodeInsert(curr, k);

	this->balanceTree(this->mRoot);
}

void Algorithms::Btree::insertAnimation(int k, std::vector<int> line)
{
	if (this->mRoot == nullptr)
	{
		this->mRoot = new BtreeNode();
		this->initializeNode(this->mRoot);
		this->mRoot->key[0] = k;
		this->mRoot->size = 1;
		this->mRoot->id = this->mVisualization.createBlock({ k });
		this->mVisualization.highlightBlock(this->mRoot->id);
		this->balanceTree(this->mRoot);
		this->newScene({line[1]});
		this->mVisualization.unhighlightBlock(this->mRoot->id);
		return;
	}

	if (mRoot->size == 2 * minDegree - 1)
	{
		this->newScene({line[2]});
		this->mVisualization.highlightBlock(this->mRoot->id);

		this->newScene({line[2]});
		this->mVisualization.resetColor();

		BtreeNode* newRoot = new BtreeNode();
		this->initializeNode(newRoot);
		newRoot->id = this->mVisualization.createBlock({});
		this->mVisualization.moveBlock(newRoot->id, this->mVisualization.getBlockPos(this->mRoot->id, 0) - Vector2{ 0, 2 * HEIGHT });
		newRoot->leaf = false;
		newRoot->child[0] = mRoot;
		splitChildAnimation(newRoot, 0, { line[3] });
		newRoot->idEdge[0] = this->mVisualization.createEdgeOffSet(
			this->mVisualization.getBlockPos(newRoot->id, 0), this->mVisualization.getBlockMid(mRoot->id)
		);
		mRoot = newRoot;
		this->balanceTree(this->mRoot);
	}
	BtreeNode* curr = mRoot;
	while (!curr->leaf)
	{
		this->newScene({line[0]});
		this->mVisualization.highlightBlock(curr->id);

		this->newScene({line[0]});
		this->mVisualization.unhighlightBlock(curr->id);

		int index = curr->size - 1;
		while (index >= 0 && k < curr->key[index])
			index--;
		index++;

		if (curr->idEdge[index])
		{
			this->newScene({line[0]});
			this->mVisualization.highlightEdge(curr->idEdge[index]);
		}

		if (curr->child[index]->size == 2 * minDegree - 1)
		{
			splitChildAnimation(curr, index, { line[2], line[3] });
			this->createEdge(this->mRoot);
			this->newScene({line[3]});
			this->balanceTree(this->mRoot);
			if (curr->key[index] < k)
				index++;
		}
		curr = curr->child[index];
	}

	nodeInsertAnimation(curr, k, { line[1] });

	this->balanceTree(this->mRoot);
	this->newScene({line[1]});
	this->mVisualization.highlightBlock(curr->id); 
	this->newScene({line[1]});
	this->mVisualization.unhighlightBlock(curr->id);
}

int Algorithms::Btree::removeAnimation(int k, std::vector<int> line)
{
	BtreeNode* curr = this->mRoot; 
	while (true)
	{
		this->balanceTree(this->mRoot);

		if (curr->id)
		{
			this->newScene({line[0]});
			this->mVisualization.highlightBlock(curr->id);
			this->newScene({line[0]});
			this->mVisualization.unhighlightBlock(curr->id);
		}

		unsigned i = findIndex(curr, k);
		
		if (i < curr->size && k == curr->key[i])
		{
			int toReturn = curr->key[i];

			if (curr->leaf)
			{
				nodeDelete(curr, i, {line[1], line[2]});
			}

			else {
				BtreeNode* leftKid = curr->child[i];
				BtreeNode* rightKid = curr->child[i + 1];

				if (leftKid->size >= minDegree)
				{
					while (!(leftKid->leaf))
					{
						fixChildSize(leftKid, leftKid->size, line[4]);
						leftKid = leftKid->child[leftKid->size];
					}
					int oldValue = curr->key[i];
					curr->key[i] = this->nodeDelete(leftKid, leftKid->size - 1, {line[4]});
					if (curr->id)
					{
						this->newScene({line[4]});
						this->mVisualization.updateValue(curr->id, oldValue, curr->key[i]);
					}
				}

				else if (rightKid->size >= minDegree)
				{
					while (!(rightKid->leaf))
					{
						fixChildSize(rightKid, 0, line[5]);
						rightKid = rightKid->child[0];
					}
					int oldValue = curr->key[i];
					curr->key[i] = this->nodeDelete(rightKid, 0, {line[5]});
					if (curr->id)
					{
						this->newScene({line[5]});
						this->mVisualization.updateValue(curr->id, oldValue, curr->key[i]);
					}
				}

				else {
					this->mergeChildren(curr, i, line[6]);
					curr = leftKid; 
					this->mVisualization.resetColor();
					continue;
				}
			}
			return toReturn;
		}

		else {
			if (curr->leaf)
			{
				throw (BTREE_EXCEPTION) REMOVE_KEY_NOT_FOUND; 
			}

			if (this->mVisualization.isEdgeExist(curr->idEdge[i]))
			{
				this->newScene({line[0]});
				this->mVisualization.highlightEdge(curr->idEdge[i]);
			}

			if (curr->child[i]->size < minDegree)
			{
				this->newScene({line[7]});
				this->mVisualization.highlightBlock(curr->child[i]->id); 
				this->newScene({line[7]});
				this->mVisualization.unhighlightBlock(curr->child[i]->id);
			}

			char result = fixChildSize(curr, i, line[7]);
			if (result == NEW_ROOT)
			{
				curr = this->mRoot; 
			}
			else {
				curr = curr->child[this->findIndex(curr, k)];
			}
		}
	}
}

void Algorithms::Btree::createEdge(BtreeNode* root)
{
	if (root == nullptr)
		return;
	if (!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
		{
			if (root->idEdge[i] == 0 && root->child[i])
			{
				root->idEdge[i] = this->mVisualization.createEdgeOffSet(
					this->mVisualization.getBlockPos(root->id, i), this->mVisualization.getBlockMid(root->child[i]->id)
				);
			}
			createEdge(root->child[i]);
		}
	}
}

void Algorithms::Btree::createNode(BtreeNode*& root)
{
	if (root == nullptr)
		return; 
	
	std::vector<int> list;
	for (int i = 0; i < root->size; ++i)
	{
		list.push_back(root->key[i]);
	}

	if (root->id == 0)
	{
		if (list.size())
			root->id = this->mVisualization.createBlock(list);
	}
	if (!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
			createNode(root->child[i]);
	}
}

void Algorithms::Btree::setNodePos(BtreeNode*& root)
{
	if (root == nullptr)
		return; 
	std::queue<BtreeNode*> q; 
	q.push(root); 
	std::vector<std::vector<BtreeNode*>> mLevel; 
	while (!q.empty())
	{
		int size = q.size(); 
		std::vector<BtreeNode*> currLevel;
		while (size--)
		{
			BtreeNode* curr = q.front(); 
			q.pop(); 
			currLevel.push_back(curr); 
			if (!curr->leaf)
			{
				for (int i = 0; i <= curr->size; ++i)
					if (curr->child[i])
						q.push(curr->child[i]);
			}
		}
		mLevel.push_back(currLevel);
	}
	int levelSize = mLevel.size(); 
	Vector2 StartPos = { Constant::WINDOW_WIDTH * Helper::scaleFactorX() / 2, (levelSize - 1) * VERTICAL_SPACE + 100};
	for (auto child : mLevel.back())
	{
		StartPos.x -= (child->size * WIDTH / 2);
	}
	StartPos.x -= (HORIZONTAL_SPACE * (mLevel.back().size() - 1) / 2); 
	for (int i = levelSize - 1; i >= 0; --i)
	{
		for (int j = 0; j < mLevel[i].size(); ++j)
		{
			if (i == levelSize - 1)
			{
				Vector2 pos; 
				pos.x = StartPos.x;
				pos.y = StartPos.y;
				if (j > 0)
					pos.x = this->mVisualization.getBlockPos(mLevel[i][j - 1]->id, mLevel[i][j - 1]->size ).x + HORIZONTAL_SPACE;
				if(mLevel[i][j]->id)
					this->mVisualization.moveBlock(mLevel[i][j]->id, pos);
			}
			else {
				if (mLevel[i][j]->leaf == false)
				{
					Vector2 posStart = this->mVisualization.getBlockPos(mLevel[i][j]->child[0]->id, 0);
					Vector2 posEnd = this->mVisualization.getBlockPos(mLevel[i][j]->child[0]->id, mLevel[i][j]->child[0]->size);
					float countSize = 0;
					for (int k = 0; k <= mLevel[i][j]->size; ++k)
					{
						countSize += WIDTH * mLevel[i][j]->child[k]->size;
						posEnd = this->mVisualization.getBlockPos(mLevel[i][j]->child[k]->id, mLevel[i][j]->child[k]->size);
					}
					countSize += (mLevel[i][j]->size) * HORIZONTAL_SPACE / 2;
					Vector2 pos; 
					pos.x = posStart.x + (posEnd.x - posStart.x) / 2 - (mLevel[i][j]->size * WIDTH) / 2;
					pos.y = posStart.y - VERTICAL_SPACE - HEIGHT; 
					if (mLevel[i][j]->id)
						this->mVisualization.moveBlock(mLevel[i][j]->id, pos);
				}
			}

		}
	}
}


void Algorithms::Btree::setEdgePos(BtreeNode*& root)
{
	if (root == nullptr)
		return;
	if(!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
		{
			if (root->child[i] && root->child[i]->id && root->idEdge[i])
			{
				this->mVisualization.moveEdgeSource(root->idEdge[i], this->mVisualization.getBlockPos(root->id, i));
				this->mVisualization.moveEdgeDes(root->idEdge[i], this->mVisualization.getBlockMid(root->child[i]->id));
			}
			setEdgePos(root->child[i]);
		}
	}
}

void Algorithms::Btree::removeBtree(BtreeNode*& root)
{
	if (root == nullptr)
		return;

	if (!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
		{
			removeBtree(root->child[i]);
		}
	}

	delete root; 
}

void Algorithms::Btree::balanceTree(BtreeNode*& root)
{
	this->modifyDistance(root);
	this->setNodePos(root);
	this->setEdgePos(root);
}

void Algorithms::Btree::splitChild(BtreeNode* root, int index)
{
	BtreeNode* toSplit = root->child[index];
	BtreeNode* newNode = new BtreeNode();
	this->initializeNode(newNode);
	newNode->leaf = toSplit->leaf;
	newNode->size = minDegree - 1;
	newNode->id = this->mVisualization.createBlock({});
	this->mVisualization.moveBlock(newNode->id, this->mVisualization.getBlockPos(toSplit->id, toSplit->size) - Vector2{ 0, HEIGHT });

	for (unsigned j = 0; j < minDegree - 1; j++)
	{
		newNode->key[j] = toSplit->key[j + minDegree];
		this->mVisualization.eraseValue(toSplit->id, toSplit->key[j + minDegree]);
		this->mVisualization.addValue(newNode->id, newNode->key[j]);
		this->mVisualization.moveBlock(newNode->id, this->mVisualization.getBlockPos(toSplit->id, toSplit->size - j - 1) - Vector2{ 0, HEIGHT });
	}

	if (!toSplit->leaf)
	{
		for (unsigned j = 0; j < minDegree; j++)
		{
			newNode->child[j] = toSplit->child[j + minDegree];
			if (toSplit->idEdge[j + minDegree])
			{
				newNode->idEdge[j] = toSplit->idEdge[j + minDegree];
				toSplit->idEdge[j + minDegree] = 0;
			}
		}
	}
	toSplit->size = minDegree - 1;

	nodeInsert(root, toSplit->key[minDegree - 1]);

	this->mVisualization.eraseValue(toSplit->id, toSplit->key[minDegree - 1]);
	if (root->idEdge[index])
	{
		this->mVisualization.moveEdgeDes(root->idEdge[index], this->mVisualization.getBlockMid(toSplit->id));
	}

	root->child[index + 1] = newNode;
	if (root->idEdge[index + 1] == 0)
	{
		root->idEdge[index + 1] = this->mVisualization.createEdgeOffSet(
			this->mVisualization.getBlockPos(root->id, index + 1), this->mVisualization.getBlockMid(newNode->id));
	}
	else {
		if (this->mVisualization.getEdgeSource(root->idEdge[index + 1]) != this->mVisualization.getBlockPos(root->id, index + 1) ||
			this->mVisualization.getEdgeDes(root->idEdge[index + 1]) != this->mVisualization.getBlockMid(newNode->id))
		{
			root->idEdge[index + 1] = this->mVisualization.createEdgeOffSet(
				this->mVisualization.getBlockPos(root->id, index + 1), this->mVisualization.getBlockMid(newNode->id));
		}
	}
}

void Algorithms::Btree::splitChildAnimation(BtreeNode* root, int index, std::vector<int> line)
{
	BtreeNode* toSplit = root->child[index];
	BtreeNode* newNode = new BtreeNode();
	this->initializeNode(newNode);
	newNode->leaf = toSplit->leaf;
	newNode->size = minDegree - 1;
	newNode->id = this->mVisualization.createBlock({});
	this->mVisualization.moveBlock(newNode->id, this->mVisualization.getBlockPos(toSplit->id, toSplit->size) - Vector2{0, HEIGHT});

	for (unsigned j = 0; j < minDegree - 1; j++)
	{
		newNode->key[j] = toSplit->key[j + minDegree];
		this->newScene(line);
		this->mVisualization.eraseValue(toSplit->id, toSplit->key[j + minDegree]);
		this->mVisualization.addValue(newNode->id, newNode->key[j]);
		this->mVisualization.moveBlock(newNode->id, this->mVisualization.getBlockPos(toSplit->id, toSplit->size - j - 1) - Vector2{ 0, HEIGHT });
	}

	if (!toSplit->leaf)
	{
		for (unsigned j = 0; j < minDegree; j++)
		{
			newNode->child[j] = toSplit->child[j + minDegree];
			if (toSplit->idEdge[j + minDegree])
			{
				newNode->idEdge[j] = toSplit->idEdge[j + minDegree];
				toSplit->idEdge[j + minDegree] = 0;
			}
		}
	}
	toSplit->size = minDegree - 1;

	nodeInsertAnimation(root, toSplit->key[minDegree - 1], line);

	this->mVisualization.eraseValue(toSplit->id, toSplit->key[minDegree - 1]);
	if (root->idEdge[index])
	{
		this->mVisualization.moveEdgeDes(root->idEdge[index], this->mVisualization.getBlockMid(toSplit->id));
	}

	root->child[index + 1] = newNode;
	if (root->idEdge[index + 1] == 0)
	{
		root->idEdge[index + 1] = this->mVisualization.createEdgeOffSet(
			this->mVisualization.getBlockPos(root->id, index + 1), this->mVisualization.getBlockMid(newNode->id));
	}
	else {
		if (this->mVisualization.getEdgeSource(root->idEdge[index + 1]) != this->mVisualization.getBlockPos(root->id, index + 1) ||
			this->mVisualization.getEdgeDes(root->idEdge[index + 1]) != this->mVisualization.getBlockMid(newNode->id))
		{
			root->idEdge[index + 1] = this->mVisualization.createEdgeOffSet(
				this->mVisualization.getBlockPos(root->id, index + 1), this->mVisualization.getBlockMid(newNode->id));
		}
	}
}

unsigned Algorithms::Btree::nodeInsert(BtreeNode* root, int k)
{
	int i;
	for (i = root->size; i > 0 && k < root->key[i - 1]; i--)
	{
		root->key[i] = root->key[i - 1];
		if (root->idEdge[i])
		{
			this->mVisualization.removeEdge(root->idEdge[i]);
			root->idEdge[i] = 0;
		}
		root->child[i + 1] = root->child[i];
	}

	root->child[i + 1] = root->child[i];
	root->key[i] = k;
	root->size++;

	if (root->id)
	{
		this->mVisualization.addValue(root->id, k);

		for (int j = root->size; j > i + 1; --j)
		{
			if (root->child[j] && root->idEdge[j] == 0)
			{
				root->idEdge[j] = this->mVisualization.createEdgeOffSet(
					this->mVisualization.getBlockPos(root->id, j), this->mVisualization.getBlockMid(root->child[j]->id)
				);
			}
			else if (root->child[j])
			{
				if (this->mVisualization.getEdgeSource(root->idEdge[j]) != this->mVisualization.getBlockPos(root->id, j) ||
					this->mVisualization.getEdgeDes(root->idEdge[j]) != this->mVisualization.getBlockMid(root->child[j]->id))
				{
					root->idEdge[j] = this->mVisualization.createEdgeOffSet(
						this->mVisualization.getBlockPos(root->id, j), this->mVisualization.getBlockMid(root->child[j]->id)
					);
				}
			}
		}
	}

	return i;
}

unsigned Algorithms::Btree::nodeInsertAnimation(BtreeNode*& root, int k, std::vector<int> line)
{
	int i;
	for (i = root->size; i > 0 && k < root->key[i - 1]; i--)
	{
		root->key[i] = root->key[i - 1];
		if (root->idEdge[i])
		{
			this->newScene(line);
			this->mVisualization.removeEdge(root->idEdge[i]);
			root->idEdge[i] = 0;
		}
		root->child[i + 1] = root->child[i];
	}

	root->child[i + 1] = root->child[i];
	root->key[i] = k;
	root->size++;

	if (root->id)
	{
		this->newScene(line);
		this->mVisualization.addValue(root->id, k);

		for (int j = root->size; j > i + 1; --j)
		{
			if (root->child[j] && root->idEdge[j] == 0)
			{
				root->idEdge[j] = this->mVisualization.createEdgeOffSet(
					this->mVisualization.getBlockPos(root->id, j), this->mVisualization.getBlockMid(root->child[j]->id)
				);
			}
			else if (root->child[j])
			{
				if (this->mVisualization.getEdgeSource(root->idEdge[j]) != this->mVisualization.getBlockPos(root->id, j) ||
					this->mVisualization.getEdgeDes(root->idEdge[j]) != this->mVisualization.getBlockMid(root->child[j]->id))
				{
					root->idEdge[j] = this->mVisualization.createEdgeOffSet(
						this->mVisualization.getBlockPos(root->id, j), this->mVisualization.getBlockMid(root->child[j]->id)
					);
				}
			}
		}
	}

	return i;
}

unsigned Algorithms::Btree::nodeDelete(BtreeNode* root, int index, std::vector<int> line)
{
	int toReturn = root->key[index];
	if (root->id)
	{
		this->newScene(line);
		this->mVisualization.eraseValue(root->id, toReturn);
		if (root->idEdge[root->size])
		{
			this->mVisualization.removeEdge(root->idEdge[root->size]); 
			root->idEdge[root->size] = 0;
		}
	}
	root->size--;
	while (index < root->size)
	{
		root->key[index] = root->key[index + 1]; 
		root->child[index + 1] = root->child[index + 2];
		index++;
	}

	if (root->size == 0)
	{
		if (root->id)
		{
			this->mVisualization.removeBlock(root->id);
			if (root->idEdge[index])
			{
				this->mVisualization.removeEdge(root->idEdge[index]);
			}
			if (root->idEdge[index + 1])
			{
				this->mVisualization.removeEdge(root->idEdge[index + 1]);
			}
		}
	}
	return toReturn;
}

unsigned Algorithms::Btree::findIndex(BtreeNode* root, int k)
{
	int i = 0; 
	while (i < root->size && root->key[i] < k)
		i++;
	return i;
}

char Algorithms::Btree::mergeChildren(BtreeNode*& root, int index, int line)
{
	BtreeNode* leftKid = root->child[index]; 
	BtreeNode* rightKid = root->child[index + 1];

	// Move item from parent to left child
	leftKid->key[leftKid->size] = this->nodeDelete(root, index, {line});

	if (leftKid->id)
	{
		this->newScene({line});
		this->mVisualization.addValue(leftKid->id, leftKid->key[leftKid->size]);
	}

	if (rightKid->id)
	{
		this->newScene({line});
		this->mVisualization.removeBlock(rightKid->id);
	}

	int j = ++(leftKid->size);

	//Move everything from rightKid into leftKid
	for (int k = 0; k < rightKid->size; ++k)
	{
		leftKid->key[j + k] = rightKid->key[k];
		if (leftKid->id)
		{
			this->newScene({line});
			this->mVisualization.addValue(leftKid->id, leftKid->key[j + k]);
		}
		leftKid->child[j + k] = rightKid->child[k];
		leftKid->idEdge[j + k] = rightKid->idEdge[k];
	}
	leftKid->size += rightKid->size;
	leftKid->child[leftKid->size] = rightKid->child[rightKid->size];
	leftKid->idEdge[leftKid->size] = rightKid->idEdge[rightKid->size];


	// If parent is empty, it must have been the root
	if (root->size == 0)
	{
		this->mRoot = leftKid; 
		return NEW_ROOT;
	}

	return MODIFIED_NOT_ROOT;
}

char Algorithms::Btree::fixChildSize(BtreeNode* root, int index, int line)
{
	BtreeNode* kid = root->child[index];

	// If need to modify
	if (kid->size < minDegree)
	{
		if (index != 0 && root->child[index - 1]->size >= minDegree)
		{
			BtreeNode* leftKid = root->child[index - 1];

			unsigned i = this->nodeInsertAnimation(kid, root->key[index - 1], { line });
			if(root->id)
				this->mVisualization.eraseValue(root->id, root->key[index - 1]);

			for (; i != 0; i--)
			{
				kid->child[i] = kid->child[i - 1];
			}
			kid->child[0] = leftKid->child[leftKid->size];
			root->key[index - 1] = this->nodeDelete(leftKid, leftKid->size - 1, {line});
			if (root->id)
			{
				this->newScene({line});
				this->mVisualization.addValue(root->id, root->key[index - 1]);
			}
			if (kid->id)
			{
				for (int i = 0; i <= kid->size; ++i)
				{
					if (kid->child[i])
					{
						if (kid->idEdge[i])
							this->mVisualization.moveEdgeDes(kid->idEdge[i], this->mVisualization.getBlockMid(kid->child[i]->id));
						else
							kid->idEdge[i] = this->mVisualization.createEdgeOffSet(
								this->mVisualization.getBlockPos(kid->id, i), this->mVisualization.getBlockMid(kid->child[i]->id)
							);
					}
				}
			}
		}

		else if (index != root->size && root->child[index + 1]->size >= minDegree)
		{
			BtreeNode* rightKid = root->child[index + 1];
			nodeInsertAnimation(kid, root->key[index], { line });
			if (root->id)
			{
				this->mVisualization.eraseValue(root->id, root->key[index]);
			}
			kid->child[kid->size] = rightKid->child[0];
			if (kid->idEdge[kid->size] == 0 && kid->id && rightKid->child[0])
			{
				this->newScene({ line });
				kid->idEdge[kid->size] = this->mVisualization.createEdgeOffSet(
					this->mVisualization.getBlockPos(kid->id, kid->size), this->mVisualization.getBlockMid(rightKid->child[0]->id)
				);
			}
			rightKid->child[0] = rightKid->child[1];
			root->key[index] = nodeDelete(rightKid, 0,{line});
			if (root->id)
				this->mVisualization.addValue(root->id, root->key[index]);
		}

		else if (index != 0)
			return this->mergeChildren(root, index - 1, line);

		else
			mergeChildren(root, index, line);

		return MODIFIED_NOT_ROOT;
	}
}

void Algorithms::Btree::search(int k)
{
	BtreeNode* x = this->mRoot; 
	while (true)
	{
		this->newScene({0}); 
		this->mVisualization.highlightBlock(x->id);

		unsigned i = findIndex(x, k);

		if (i < x->size && x->key[i] == k)
		{
			this->mVisualization.setLabelBlock(x->id, "index " + std::to_string(i));
			this->newScene({1});
			this->mVisualization.setLabelBlock(x->id, "");
			return; 
		}
		else if (x->leaf)
		{
			this->newScene({ 2 });
			this->mVisualization.setLabelBlock(x->id, "not found");
			this->newScene({3});
			this->mVisualization.setLabelBlock(x->id, "");
			return;
		}
		else {
			this->newScene({4}); 
			this->mVisualization.unhighlightBlock(x->id);
			if (x->idEdge[i])
			{
				this->newScene({4}); 
				this->mVisualization.highlightEdge(x->idEdge[i]);
			}
			x = x->child[i];
		}
	}
}

bool Algorithms::Btree::checkExist(int k)
{
	BtreeNode* x = this->mRoot;
	while (true)
	{
		unsigned i = findIndex(x, k);

		if (i < x->size && x->key[i] == k)
		{
			return true;
		}
		else if (x->leaf)
		{
			return false;
		}
		else {
			x = x->child[i];
		}
	}
}

void Algorithms::Btree::initializeNode(BtreeNode* node)
{
	node->idEdge = new int[4];
	for (int i = 0; i < 4; ++i)
		node->idEdge[i] = 0;
}

void Algorithms::Btree::freeNode(BtreeNode*& root)
{
	if (root == nullptr)
		return; 
	if (!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
			freeNode(root->child[i]);
	}
	delete root->idEdge;
	delete (root);
}

void Algorithms::Btree::modifyDistance(BtreeNode* root)
{
	int countNode = this->countNode(root); 

	if (countNode <= 10)
		this->HORIZONTAL_SPACE = 110;
	else if (countNode <= 20)
		this->HORIZONTAL_SPACE = 30;
	else if (countNode <= 30)
		this->HORIZONTAL_SPACE = 10;
}

int Algorithms::Btree::countNode(BtreeNode* root)
{
	if (root == nullptr)
		return 0; 
	int count = 0; 
	if (!root->leaf)
	{
		for (int i = 0; i <= root->size; ++i)
			count += countNode(root->child[i]);
	}
	return count + 1;
}


