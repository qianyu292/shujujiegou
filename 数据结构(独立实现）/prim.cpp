#include<vector>
#include<queue>
using namespace std;
class State
{
	int node;

	int weight;

public:
	State(int node, int weight):node(node), weight(weight){}
	int getnode()const{ return node; }
	int getweight()const {return weight;}
};
struct Compare
{
	bool operator()(const State& a, const State& b)
	{
		return a.getweight() > b.getweight();
	}
};
int prim(vector<vector<pair<int, int>>>& graph)
{
	int weightsum = 0;

	vector<bool>visited(graph.size(), false);

	priority_queue<State, vector<State>, Compare>pq;

	pq.emplace(0, 0);

	while (!pq.empty())
	{
		State state = pq.top(); pq.pop();
		int curnode = state.getnode();
		int curweight = state.getweight();
		if (visited[curnode])
		{
			continue;
		}
		weightsum += curweight;
		visited[curnode] = true;
		for (auto& edge : graph[curnode])
		{
			int nextnode = edge.first;

			int nextweight = edge.second;

			if (visited[nextnode])
			{
				continue;
			}
			pq.emplace(nextnode, nextweight);
		}
	}
	for (int i = 0; i < visited.size(); ++i)
	{
		if (!visited[i])
		{
			return -1;
		}
	}
	return weightsum;
}