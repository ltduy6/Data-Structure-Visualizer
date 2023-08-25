#pragma once
#include "Algorithm.h"
#include "../Helper/GlobalVar.h"
#include "Btree.h"

namespace Algorithms {
	class AVL : public Algorithm
	{
	public:
		float RADIUS = 60 * Helper::scaleFactorX() / 2;
		float VERTICAL_SPACE = 100 * Helper::scaleFactorY();
		float HORIZONTAL_SPACE = 50 * Helper::scaleFactorX();
		float MODIFIER = 0;
	public:
		AVL(Visualize::Visualization& visualization); 
		~AVL(); 
	public:
		void InitRandomFixSize(int size); 
		void Init(std::vector<int>& list);
		void Insert(int value); 
		void Remove(int value);
		void Search(int value);
		void Update(int oldValue, int newValue);
	private:
		class Node {
		public:
			Node() : left{ nullptr }, right{ nullptr }, parent{ nullptr } {};
			~Node() {
				delete left; 
				delete right; 
			}
		public:
			int value{ 0 };
			int id{ 0 };
			int Alignment{ 0 };
			int idEdgeLeft{ 0 }; 
			int idEdgeRight{ 0 };

			Node*left; 
			Node* right; 
			Node* parent;
		};
	private:
		int mSize{ 0 }; 
		int mHeight{ 0 };
		Node* mRoot{ nullptr };
		Node* mVisual{ nullptr };
		bool finishRotation{ true };
		bool helper{ false };
	private:
		void sceneReset();
	private:
		Node* InitUntil(Node*& root, Node*& parent, int value, int indexCode, bool isAnimation = true);
		Node* RemoveUntil(Node*& root, int value);
		Node* rotateLeft(Node*& root); 
		Node* rotateRight(Node*& root); 

		void searchValue(Node* root, int value);
		void removeAVL(Node*& root); 
		void RotateUntil(Node*& root, int indexCode);
		void traverse(Node*& root, Vector2 pos, int level, int& count); 
		void modifyDistance(Node*& root);
		void BalanceTree(Node*& root);
		void addEdge(Node*& root); 
		int Height(Node* root);
		int Width(Node* root);
		int countNode(Node* root);
		int getBalance(Node* root);
	};
}
