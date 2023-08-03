#pragma once
#include "Algorithm.h"

namespace Algorithms {
	class Btree : public Algorithm
	{
	public:
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
			BtreeNode* child[4];
		};
	private:
		BtreeNode* mRoot{ nullptr };
		unsigned minDegree{ 2 };
	private:
		void sceneReset();
	private:
		void insertNonAni(int k);
		void insertAnimation(int k, std::vector<int> line);
		void splitChild(BtreeNode* root, int index);
		void splitChildAnimation(BtreeNode* root, int index, std::vector<int> line);

		void search(int k);
		bool checkExist(int k);

		int removeAnimation(int k, std::vector<int> line);
		char mergeChildren(BtreeNode*& root, int index, int line);
		char fixChildSize(BtreeNode* root, int index, int line);

		unsigned nodeInsert(BtreeNode* root, int k);
		unsigned nodeInsertAnimation(BtreeNode*& root, int k, std::vector<int> line);
		unsigned nodeDelete(BtreeNode* root, int index, std::vector<int> line);
		unsigned findIndex(BtreeNode* root, int k);
		
		void createEdge(BtreeNode* root);
		void createNode(BtreeNode*& root);
		void setNodePos(BtreeNode*& root);
		void setEdgePos(BtreeNode*& root);
		void removeBtree(BtreeNode*& root);
		void balanceTree(BtreeNode*& root);

		void initializeNode(BtreeNode* node);
		void freeNode(BtreeNode*& root); 
		void modifyDistance(BtreeNode* root);
		int countNode(BtreeNode* root);
	};
}

