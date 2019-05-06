#include <stdio.h>
#include <vector>

#define MAX 10000

int calc_weight(const std::vector<int>* const graph, int index);

int main()
{
	int weight[MAX] = { 0, };
	int weight_sum = 0;
	int max_value = 0;
	std::vector<int> graph[MAX];

	// 입력
	int skill_sum = 143;
	std::vector<std::vector<int>> input = { {1, 2}, {1, 3}, {1, 4}, {4, 5}, {4, 6}, {4, 7} };

	// 계산
	for (int i = 0; i < input.size(); i++)
	{
		int parent = input[i][0] - 1;
		int child = input[i][1] - 1;

		if (max_value < child) {
			max_value = child;
		}

		graph[parent].push_back(child);
	}
	for (int i = 0; i <= max_value; i++)
	{
		int weight = calc_weight(graph, i);
		weight_sum += weight == 0 ? 1 : weight;
	}

	// 출력
	printf("%d\n", skill_sum / weight_sum);

	return 0;
}

int calc_weight(const std::vector<int> * const graph, int index)
{
	const std::vector<int>& target = graph[index];
	int result = 0;

	for (int i = 0; i < target.size(); i++)
	{
		if (graph[target[i]].size() == 0)
			result += 1;
		else
			result += calc_weight(graph, target[i]);
	}

	return result;
}