#include <stdio.h>
#include <iostream>
#include <vector>
#include <queue>

#define MAX_NODE 20001
#define INF 1000000000

typedef struct Vertex
{
	int index_;
	int dist_;

	bool operator <(const Vertex& other) const
	{
		return this->dist_ > other.dist_;
	}
} Vertex;

// graph infos
std::vector<std::pair<int, int>> graph[MAX_NODE];
int u_count, v_count;
int target_node;
// dijkstra infos
int min_dists[MAX_NODE];
std::priority_queue<Vertex> calc_queue;

void CalcMinWeights();

int main()
{
	// 초기화
	std::fill_n(min_dists, MAX_NODE, INF);

	// 입력
	scanf("%d%d%d", &u_count, &v_count, &target_node);
	int u, v, w;
	for (int i = 0; i < v_count; i++)
	{
		scanf("%d%d%d", &u, &v, &w);
		graph[u].push_back({ v, w });
	}

	min_dists[target_node] = 0;
	for (int i = 1; i <= u_count; i++)
		calc_queue.push({ i, min_dists[i] });

	// 계산
	CalcMinWeights();

	// 출력
	for (int i = 1; i <= u_count; i++)
	{
		if (min_dists[i] >= INF)
			printf("INF\n");
		else
			printf("%d\n", min_dists[i]);
	}

	return 0;
}

void CalcMinWeights()
{
	Vertex top = calc_queue.top();
	calc_queue.pop();

	while (!calc_queue.empty())
	{
		const std::vector<std::pair<int, int>>& dists = graph[top.index_];
		for (int i = 0; i < dists.size(); i++)
		{
			if (min_dists[dists[i].first] > min_dists[top.index_] + dists[i].second)
			{
				min_dists[dists[i].first] = min_dists[top.index_] + dists[i].second;
				calc_queue.push({ dists[i].first, min_dists[dists[i].first] });
			}
		}

		top = calc_queue.top();
		calc_queue.pop();
	}
}