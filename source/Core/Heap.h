#pragma once
#include "Algorithm.h"
#include "raylib.h"
#include "../Helper/GlobalVar.h"
#include <vector>
#include <functional>

namespace Algorithms {
	class Heap : public Algorithm
	{
	public:
		float VERTICAL_SPACE = 100 * Helper::scaleFactorY();
		float HORIZONTAL_SPACE = 700 * Helper::scaleFactorX();
		float MODIFIER = 0;
	public:
		Heap(Visualize::Visualization& visualization);
		~Heap();
	public:
		void InitRandomFixSize(int size);
		void Init(std::vector<int>& list);
		void Insert(int value);
		void Remove(int index);
		void ExtractTop();
		void setMaxHeap();
		void setMinHeap();
		int getSize() const;
	private:
		class Node {
		public:
			Node(int value) : value{value}{};
			~Node() {};
		public:
			int value{ 0 };
			int id{ 0 };
			int Alignment{ 0 };
			int idEdgeLeft{ 0 };
			int idEdgeRight{ 0 };
		};
	private:
		std::vector<Node*> mHeap; 
		std::function<bool(int a, int b)> largerThan;
		bool isMaxHeap{ true };
	private:
		void sceneReset();
	private:
		void insertAnimation(int value);
		void insertNonAnimation(int value);
		void deleteAnimation(int index);
		void upHeapAnimation(int index, std::vector<int> line);
		void upHeapNonAnimation(int index);
		void downHeapAnimation(int index, std::vector<int> line);
		void extractMax(std::vector<int> line);

		Vector2 getPos(int i);
		int parent(int i);
		int left(int i); 
		int right(int i);

	};
}

