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
		static constexpr Vector2 STARTING_POINT = Vector2{ Constant::WINDOW_WIDTH / 2, 100 };
		static constexpr float RADIUS = 20;
		float VERTICAL_SPACE = 100;
		float HORIZONTAL_SPACE = 700;
		float MODIFIER = 0;
	public:
		Heap(Visualize::Visualization& visualization);
		~Heap();
	public:
		void InitRandomFixSize(int size);
		void Init(std::vector<int>& list);
		void Insert(int value);
		void Remove(int index);
		void Search(int value);
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
		void downHeapAnimation(int index);
		void extractMax();

		Vector2 getPos(int i);
		int parent(int i);
		int left(int i); 
		int right(int i);

	};
}

