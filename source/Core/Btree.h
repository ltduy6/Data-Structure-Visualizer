#pragma once
#include "Algorithm.h"

namespace Algorithms {
	class Btree : public Algorithm
	{
	public:
		static constexpr Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH / 2, 100 };
		static constexpr float WIDTH = 100; 
		static constexpr float HEIGHT = 60;
		float VERTICAL_SPACE = 100;
		float HORIZONTAL_SPACE = 30;
		float MODIFIER = 0;
	public:
		Btree(Visualize::Visualization& visualization); 
		~Btree(); 
	public:
		void InitRandomFixSize(int size);
		void Init(std::vector<int>& list);
		void Insert(int value);
		void Remove(int value);
		void Search(int value);
		void Update(int oldValue, int newValue);
	private:
		struct BtreeNode {
			int key[3]{ 0 };
			unsigned size{ 0 };
			int id{ 0 };
			int* idEdge;
			bool leaf{ true };
			BtreeNode* parent;
			BtreeNode* child[4];
		};
	private:
		BtreeNode* mRoot{ nullptr };
		unsigned minDegree{ 2 };
	private:
		void sceneReset();
	private:
		void insertNonAni(int k);
		void insertAnimation(int k);

		int removeAnimation(int k);


		void setParent(BtreeNode*& root, BtreeNode*& parent);
		void createEdge(BtreeNode* root);
		void createNode(BtreeNode*& root);
		void setNodePos(BtreeNode*& root);
		void setEdgePos(BtreeNode*& root);
		void removeBtree(BtreeNode*& root);
		void balanceTree(BtreeNode*& root);

		void splitChild(BtreeNode* root, int index);
		void splitChildAnimation(BtreeNode* root, int index);

		void search(int k);
		bool checkExist(int k);


		unsigned nodeInsert(BtreeNode* root, int k);
		unsigned nodeInsertAnimation(BtreeNode*& root, int k);
		unsigned nodeDelete(BtreeNode* root, int index);
		unsigned findIndex(BtreeNode* root, int k);

		char mergeChildren(BtreeNode*& root, int index); 
		char fixChildSize(BtreeNode* root, int index);
		

		void traverse(BtreeNode* root);
		void initializeNode(BtreeNode* node);

		
		void freeNode(BtreeNode*& root); 
		int Height(BtreeNode* root);
		void modifyDistance(BtreeNode* root);
		int countNode(BtreeNode* root);
	};
}

