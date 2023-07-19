#pragma once
#include "Algorithm.h"
#include "../Helper/GlobalVar.h"

namespace Algorithms {
	class AVL : public Algorithm
	{
	public:
		static constexpr Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH / 2, 100 };
		static constexpr float RADIUS = 20;
		float VERTICAL_SPACE = 100;
		float HORIZONTAL_SPACE = 50;
		float MODIFIER = 0;
	public:
		AVL(Visualize::Visualization& visualization); 
		~AVL(); 
	public:
		void InitRandomFixSize(int size); 
		void Init(std::vector<int>& list);
		void Insert(int value); 
		void Remove(int value);
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
			int height{ 1 };
			int Alignment{ 0 };
			int idEdgeLeft{ 0 }; 
			int idEdgeRight{ 0 };
			int idEdge{ 0 }; 

			Node*left; 
			Node* right; 
			Node* parent;

			std::map<int, std::string> references; 
		};
	private:
		int mSize{ 0 }; 
		int mHeight{ 0 };
		Node* mRoot{ nullptr };
		Node* mVisual{ nullptr };
		bool finishRotation{ true };
		bool helper{ false };
		std::map<std::pair<int, int>, int> mEdgeMap;
	private:
		void sceneReset();
	private:
		Node* InitUntil(Node*& root, Node*& parent, int value);
		Node* RemoveUntil(Node*& root, int value);
		Node* SortedArrayToAVL(std::vector<int>& nums, int start, int end);
		Node* rotateLeft(Node*& root); 
		Node* rotateRight(Node*& root); 
		Node* searchValue(Node* root, int value);
		Node* copyTree(Node* root);

		void printParent(Node* root);
		void removeAVL(Node*& root); 
		void printBST(Node* root);
		void RotateUntil(Node*& root);
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
