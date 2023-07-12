#pragma once
#include "Algorithm.h"
#include "../Helper/GlobalVar.h"

namespace Algorithms {
	class AVL : public Algorithm
	{
	public:
		static constexpr Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH / 2, 100 };
		static constexpr float VERTICAL_SPACE = 100;
		static constexpr float RADIUS = 20;
		float HORIZONTAL_SPACE = 50;
		float MODIFIER = 0;
	public:
		AVL(Visualize::Visualization& visualization); 
		~AVL(); 
	public:
		void InitRandomFixSize(int size); 
		void Init(std::vector<int>& list);
	private:
		class Node {
		public:
			typedef std::shared_ptr<Node> Ptr; 
			Node() : left{ nullptr }, right{ nullptr } {};
		public:
			int value{ 0 };
			int id{ 0 };
			int height{ 1 };
			int Alignment{ 0 };

			Node::Ptr left; 
			Node::Ptr right; 

			std::map<int, std::string> references; 
		};
	private:
		int mSize{ 0 }; 
		int mHeight{ 0 };
		Node::Ptr mRoot{ nullptr };
	private:
		Node::Ptr InitUntil(Node::Ptr& root, int value, int Alignment);
		Node::Ptr SortedArrayToAVL(std::vector<int>& nums, int start, int end);
		void traverse(Node::Ptr& root, Vector2 pos, int level, int& count); 
		void modifyDistance();
		void BalanceTree();
		void addEdge(); 
		float Height(Node::Ptr root);
		float Width(Node::Ptr root);
		int countNode(Node::Ptr root);
		void sceneReset();
		void sceneInit(); 
		void newScene(std::vector<int> lines); 
	};
}
