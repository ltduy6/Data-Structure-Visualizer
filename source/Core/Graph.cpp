#include "Graph.h"
#include <iostream>
#include <queue>

Algorithms::Graph::Graph(Visualize::Visualization& visualization) : Algorithm(visualization)
{
}

Algorithms::Graph::~Graph()
{
}

void Algorithms::Graph::InitRandomFixSize(int size)
{
	std::vector<std::vector<int>> matrix; 
	matrix.resize(size);
	for (int i = 0; i < size; ++i)
		matrix[i].resize(size);
	for (int i = 0; i < size; ++i)
	{
		for (int j = i + 1; j < size; ++j)
		{
			if (!(i & 1))
			{
				matrix[i][j] = Helper::rand(1, 20);
			}
			else
				matrix[i][j] = -1;
		}
	}
	this->InitFromMatrix(matrix);
}

void Algorithms::Graph::InitFromEdge(listEdge& listEdge)
{
	this->sceneReset();
	for (auto& edge : listEdge)
	{
		if (this->mNode.find(edge.first.first) == this->mNode.end())
		{
			this->mNode.emplace(edge.first.first, this->mVisualization.createCirNode(edge.first.first));
		}
		if (this->mNode.find(edge.first.second) == this->mNode.end())
		{
			this->mNode.emplace(edge.first.second, this->mVisualization.createCirNode(edge.first.second));
		}
		if (this->mEdge.find(edge.first) == this->mEdge.end() && edge.first.first != edge.first.second)
		{
			int newEdge = this->mVisualization.createEdge(this->getPos(edge.first.first), this->getPos(edge.first.second));
			this->mVisualization.setWeight(newEdge, std::to_string(edge.second)); 

			this->mEdge.emplace(edge.first, newEdge);
			this->mEdge.emplace(std::make_pair(edge.first.second, edge.first.first), newEdge);
		}
		if (edge.first.first != edge.first.second)
		{
			this->mList[edge.first.first].emplace(edge.first.second, edge.second);
			this->mList[edge.first.second].emplace(edge.first.first, edge.second);
		}
	}
	this->numV = this->mNode.size();

	this->balanceGraph();
}

void Algorithms::Graph::InitFromMatrix(std::vector<std::vector<int>> matrix)
{
	this->sceneReset();
	if (matrix.size() == 0)
		return;
	this->numV = matrix.size();

	for (int i = 0; i < this->numV; ++i)
	{
		this->mNode.emplace(i, this->mVisualization.createCirNode(i));
	}

	for (int i = 0; i < matrix.size(); ++i)
	{
		for (int j = i + 1; j < matrix.size(); ++j)
		{
			if (matrix[i][j] != -1)
			{
				int newEdge = this->mVisualization.createEdge(this->getPos(i), this->getPos(j));
				this->mVisualization.setWeight(newEdge, std::to_string(matrix[i][j]));

				this->mEdge.emplace(std::make_pair(i, j), newEdge);
				this->mEdge.emplace(std::make_pair(j, i), newEdge);
				this->mList[i].emplace(std::make_pair(j, matrix[i][j]));
				this->mList[j].emplace(std::make_pair(i, matrix[i][j]));
			}
		}
	}
	this->balanceGraph();
}

void Algorithms::Graph::Dijkstra(int source)
{
	this->sceneInit(); 
	std::map<int, int> dist;
	
	for (auto v : this->mNode)
	{
		if (v.first != source)
		{
			this->mVisualization.setLabel(v.second, "INF");
			dist.emplace(v.first, INF);
		}
		else
		{
			this->mVisualization.setLabel(v.second, "0");
			dist.emplace(v.first, 0);
		}
	}

	std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq; 
	pq.push({ 0, source });

	this->newScene({}); 
	this->mVisualization.highlightCirNode(this->mNode[source]);

	while (!pq.empty())
	{
		int u = pq.top().second; 
		pq.pop();

		auto adEdge = this->mList.find(u);
		if (adEdge == this->mList.end())
		{
			std::cout << u << "not from list" << '\n';
		}
		else {
			for (const auto& neighbor : adEdge->second)
			{
				int v = neighbor.first;
				int weight = neighbor.second;

				if (dist[u] + weight < dist[v])
				{
					dist[v] = dist[u] + weight;
					pq.push({ dist[v], v });

					this->newScene({});
					if (u != source)
						this->mVisualization.highlightCirNode(this->mNode[u]);
					this->mVisualization.highlightEdge(this->mEdge[std::make_pair(u, v)]);

					this->newScene({});
					this->mVisualization.resetColorCirNode(this->mNode[v]);
					this->mVisualization.highlightCirNode(this->mNode[v]);
					this->mVisualization.setLabel(this->mNode[v], std::to_string(dist[v]));

					this->newScene({}); 
					this->mVisualization.resetColorCirNode(this->mNode[v]);
					if(u != source)
						this->mVisualization.resetColorCirNode(this->mNode[u]);
				}
				else if (dist[u] != dist[v] + weight && dist[v] != dist[u] + weight && u != source)
				{
					this->mVisualization.colorEdge(this->mEdge[std::make_pair(u, v)], ColorSetting::GetInstance().get(ColorThemeID::EDGE));
				}
			}
		}
	}

	for (auto edge : this->mEdge)
	{
		if (this->mVisualization.getEdgeColor(edge.second) == ColorSetting::GetInstance().get(ColorThemeID::EDGE))
		{
			this->mVisualization.unhighlightEdge(edge.second);
		}
	}
}

void Algorithms::Graph::primMST(int source)
{
	this->sceneInit();

	std::vector<int> resV; 
	std::map<int, bool> visited; 
	for (const auto& v : this->mNode)
		visited.emplace(v.first, false);

	std::map<int, int> resE; 

	std::priority_queue <std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int>>> pq;
	pq.push({ 0, source });
	resV.push_back(source);

	this->mVisualization.highlightCirNode(this->mNode[source]);
	while (!pq.empty())
	{
		int u = pq.top().second; 
		int w = pq.top().first; 
		pq.pop(); 

		if (visited[u])
			continue; 

		visited[u] = true;

		if (u != source)
		{
			this->newScene({}); 
			int lastV = resE[u];
			this->mVisualization.highlightEdge(this->mEdge[std::make_pair(u, lastV)]);
			this->mVisualization.highlightCirNode(this->mNode[u]);
			this->newScene({}); 
			this->mVisualization.unhighlightCirNode(this->mNode[u]);
			resV.push_back(u);
		}

		auto adEdge = this->mList.find(u); 
		for (const auto& neighbor : adEdge->second)
		{
			int v = neighbor.first; 
			int w = neighbor.second; 

			if (!visited[v])
			{
				pq.push(std::make_pair(w, v));
				resE.emplace(v, u);
			}
		}
	}

	for (auto edge : this->mEdge)
	{
		if (this->mVisualization.getEdgeColor(edge.second) == ColorSetting::GetInstance().get(ColorThemeID::EDGE))
		{
			this->mVisualization.unhighlightEdge(edge.second);
		}
	}
}

void Algorithms::Graph::ConnectedCompo()
{
	this->sceneInit();
	std::vector<std::vector<int>> mComponents; 
	std::map<int, bool> visited; 
	for (const auto& v : this->mNode)
		visited.emplace(v.first, false);

	for (const auto& v : this->mNode)
	{
		if (!visited[v.first])
		{
			std::map<int, bool> component;
			DFS(v.first, visited, component);
			Color color = Helper::randColor();
			for (auto u : component)
			{
				this->mVisualization.colorCirNode(this->mNode[u.first], color);
				auto adEdge = this->mList.find(u.first);
				for (auto edge : adEdge->second)
					if (component.find(edge.first) != component.end())
						this->mVisualization.colorEdge(this->mEdge[std::make_pair(u.first, edge.first)], color);
			}
		}
	}
}

bool Algorithms::Graph::isExist(int vertex)
{
	return this->mNode.find(vertex) != this->mNode.end();
}

int Algorithms::Graph::getSize() const
{
	return this->numV;
}

Vector2 Algorithms::Graph::getPos(int value)
{
	auto found = this->mNode.find(value); 

	assert(found != this->mNode.end()); 

	return this->mVisualization.getCirNodePosition(found->second); 
}

void Algorithms::Graph::setVPos()
{
	int i = 0;
	for (const auto& v : this->mNode)
	{
		float angle = (2 * PI * i) / numV; 
		Vector2 pos = CENTER + Vector2{ RADIUS * cos(angle), RADIUS * sin(angle) }; 
		this->mVisualization.moveCirNode(v.second, pos);
		i++;
	}
}

void Algorithms::Graph::setEPos()
{
	for (const auto& e : this->mEdge)
	{
		this->mVisualization.moveEdgeSource(e.second, this->getPos(e.first.first));
		this->mVisualization.moveEdgeDes(e.second, this->getPos(e.first.second));
	}
}

void Algorithms::Graph::balanceGraph()
{
	if (this->numV >= 7)
	{
		RADIUS = 550;
		CENTER = Vector2{ Constant::WINDOW_WIDTH, Constant::WINDOW_HEIGHT } / 2 + Vector2{ 0, -150 };
	}
	this->setVPos(); 
	this->setEPos();
}

void Algorithms::Graph::sceneReset()
{
	this->mVisualization.reset(); 
	this->mNode.clear(); 
	this->mEdge.clear(); 
	this->mList.clear();
}

void Algorithms::Graph::sceneInit()
{
	mVisualization.reset(mVisualization.getLastScene());
	mVisualization.resetColor();
	mVisualization.resetLabel();
}

void Algorithms::Graph::DFS(int v, std::map<int, bool>& visited, std::map<int, bool>& component)
{
	visited[v] = true; 
	component.emplace(v, true);

	auto adEdge = this->mList.find(v); 
	for (const auto& neighbor : adEdge->second)
	{
		if (!visited[neighbor.first])
		{
			DFS(neighbor.first, visited, component);
		}
	}
}

