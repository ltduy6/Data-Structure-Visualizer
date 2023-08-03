#pragma once
#include "Algorithm.h"

const int INF = std::numeric_limits<int>::max();

namespace Algorithms {
	class Graph : public Algorithm
	{
	public:
		Graph(Visualize::Visualization& visualization); 
		~Graph();
	public:
		void InitRandomFixSize(int size);
		void InitFromEdge(listEdge& listEdge);
		void InitFromMatrix(std::vector<std::vector<int>> matrix);
		void Dijkstra(int source);
		void primMST(int source);
		void ConnectedCompo();
		bool isExist(int vertex);
		int getSize() const;
	private:
		std::map<int, int> mNode; 
		std::map<std::pair<int, int>, int> mEdge; 
		std::unordered_map<int, std::map<int, int>> mList; 
		std::vector<std::vector<int>> mMatrix; 
	private:
		int numV{ 0 };
		float RADIUS{ 400.f };
		Vector2 CENTER{ Constant::WINDOW_WIDTH / 2, Constant::WINDOW_HEIGHT / 3 };
	private:
		Vector2 getPos(int value);
		void setVPos();
		void setEPos();
		void balanceGraph();
		void sceneReset();
		void sceneInit();
		void DFS(int v, std::map<int, bool>& visited, std::map<int, bool>& component);
	};
}

