#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

#define MAX_NODE 20001
#define INF 1000000000

typedef pair<int, int> Pair;

typedef struct Priority
{
	bool operator()(const Pair& p1, const Pair& p2) const
	{
		return p1.second > p2.second;
	}
} Priority;

vector<Pair> graph[MAX_NODE];
int u_count, v_count;
int target_node;

vector<int> Dijkstra();

int main()
{
	// 입력
	scanf("%d%d%d", &u_count, &v_count, &target_node);
	int u, v, w;
	for (int i = 0; i < v_count; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		graph[u].push_back({ v, w });
	}

	// 계산
	vector<int> dists = Dijkstra();

	// 출력
	for (int i = 1; i <= u_count; i++)
	{
		if (dists[i] >= INF)
			printf("INF\n");
		else
			printf("%d\n", dists[i]);
	}

	return 0;
}

vector<int> Dijkstra()
{
	priority_queue<Pair, vector<Pair>, Priority> visited;
	vector<int> dists(u_count + 1, INF);

	dists[target_node] = 0;
	visited.push({ target_node, 0 });

	while (!visited.empty())
	{
		Pair top = visited.top();
		visited.pop();

		if (top.second != dists[top.first])
			continue;

		for (auto v : graph[top.first])
		{
			if (dists[v.first] > dists[top.first] + v.second)
			{
				dists[v.first] = dists[top.first] + v.second;
				visited.push({ v.first, dists[v.first] });
			}
		}
	}

	return dists;
}