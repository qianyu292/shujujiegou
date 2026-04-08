//有向加权图
#include<iostream>
#include<vector>
#include<stdexcept>
using namespace std;
class weightedgraph
{
public:
	struct edge
	{
		int to;
		int weight;
		edge(int to, int weight)
		{
			this->to = to;
			this->weight = weight;
		}
	};
private:
	vector<vector<edge>>graph;
public:
	weightedgraph(int n)
	{
		graph = vector<vector<edge>>(n);
	}
	void addedge(int from, int to, int weight)
	{
		graph[from].emplace_back(to,weight);
	}
	void removeedge(int from, int to)
	{
		for (auto it = graph[from].begin(); it != graph[from].end(); it++)
		{
			if (it->to == to)
			{
				graph[from].erase(it);
				break;
			}
		 }
	}
	bool hasedge(int from, int to)
	{
		for (const auto& it : graph[from])
		{
			if (it.to == to)
			{
				return true;
			}
		}
		return false;
	}
	int weight(int from, int to)
	{
		for (const auto& it : graph[from])
		{
			if (it.to == to)
			{
				return it.weight;
			}
		}
		throw invalid_argument("No such edge");
	}
	const vector<edge>neighbors(int v)
	{
		return graph[v];
	}
};