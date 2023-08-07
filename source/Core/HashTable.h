#pragma once
#include "Algorithm.h"

namespace Algorithms {
	class HashTable : public Algorithm
	{
	public:
		float HORIZONTAL_SPACE = 200 * Helper::scaleFactorX();
		float VERTICAL_SPACE = 200 * Helper::scaleFactorY();
	public:
		HashTable(Visualize::Visualization& visualization); 
		~HashTable();
	public:
		void Create(int size, int numValues);
		void InitFromFile(std::vector<int>& input);
		void Insert(int value);
		void Remove(int value);
		void Search(int value);
		int getSize() const;
	private:
		void sceneReset(); 
		void sceneInit();
		int hashFunc(int value);
		int getVisualId(int index);
		int getValueId(int index);
	private:
		int mSize{ 0 };
		std::vector<std::pair<int, int>> mTable; 
	};
}

