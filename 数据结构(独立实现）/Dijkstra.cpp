#include<queue>
#include<vector>
#include<iostream>
#include<climits>
using namespace std;

class Graph
{
private:
	int V;

	vector <vector<pair<int, int>>>adj;
public:
	Graph(int vertices) :V(vertices)
	{
		adj.resize(V);
	}
	void addEdge(int u, int v, int weight)
	{
		adj[u].push_back({v, weight});
	}
	vector<int>shortestpath(int src)
	{
		vector<int>dist(V, INT_MAX);

		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int,int>>>pq;

		pq.push({ 0,src });
		dist[src] = 0;

		while (!pq.empty())
		{
			pair<int, int>cur = pq.top();
			pq.pop();
			int u = cur.second;
			int currentval = cur.first;
			if (dist[u] < currentval)
			{
				continue;
			}
			for (const auto&edge : adj[u])
			{
				int nextu = edge.second;
				int nextval = edge.first;
				if (dist[u] + nextval < dist[nextu])
				{
					dist[nextu] = dist[u] + nextval;
					pq.push({dist[nextu],nextu });
				}
			}
		}
		return dist;
	}
	void printshortestpath(int src)
	{
		vector<int>dist = shortestpath(src);
		for (int i = 0; i < V; ++i)
		{
			if(dist[i]==INT_MAX)
			  cout << "从顶点" << i << ":INF(不可达)" << endl;
			else
			  cout << "从顶点" << i << ":"<<dist[i] << endl;
		}
	}
};