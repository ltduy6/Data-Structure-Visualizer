#pragma once
#include "Algorithm.h"
#include <map>

namespace Algorithms {
	class Trie : public Algorithm
	{
	public:
		int ELEMENT_SIZE = 60 * Helper::scaleFactorX();
		static constexpr int ALPHABET_SIZE = 26;
		float VERTICAL_SPACE = (float) 100 * Helper::scaleFactorY();
		float HORIZONTAL_SPACE = (float) 50 * Helper::scaleFactorX();
		float MODIFIER = 0;
	public: 
		Trie(Visualize::Visualization& visualization); 
		~Trie();
	public:
		void InitRandomFixSize(int size);
		void Init(std::vector<std::string>& list);
		void Insert(std::string value);
		void Remove(std::string value);
		bool Search(std::string value);
	private:
		class Node {
		public:
			std::map<char, Node*> children; 
			std::map<char, int> Edge; 
			Node* child[ALPHABET_SIZE];
			int cntChild;
			bool isEndOfWord; 
			std::string value; 
			int id; // id of circular node display this node
			Node(char c) : isEndOfWord(false), id(0), cntChild(0), value(std::string(1, c)) {
				for (int i = 0; i < ALPHABET_SIZE; ++i)
					child[i] = nullptr;
			}
		};
	private:
		Node* mRoot; 
		Node* lastChild{ nullptr };
		int maxLength{ 0 };
	private:
		void sceneReset(); 
		Vector2 getPos(int id);
		void balanceTree();
		void setNodePos(Node* root, Vector2& pos); 
		void setEdgePos(Node* root);
		void modifyDistance();
	private:
		void insertAnimation(const std::string& word, bool animation = true);
		void deleteWordAnimation(Node* node, const std::string& word, int depth = 0); 
		Node* searchAnimation(const std::string& word);
		void deleteTrie(Node* root);

		int countNode(Node* root);
	};
}

