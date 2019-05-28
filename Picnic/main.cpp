#include <stdio.h>

#define MAX_FRIEND_COUNT 10

int get_group_count(const int relations[MAX_FRIEND_COUNT][MAX_FRIEND_COUNT], int visited[MAX_FRIEND_COUNT], int current_pair_count, int start, int n)
{
	int result = 0;

	if (current_pair_count == n / 2)
		return 1;

	for (int i = start; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (!visited[i] && !visited[j] && relations[i][j])
			{
				visited[i] = visited[j] = true;
				result += get_group_count(relations, visited, current_pair_count + 1, i + 1, n);
				visited[i] = visited[j] = false;
			}		
		}
	}

	return result;
}

/*
	- Test Case

	3
	2 1
	0 1
	4 6
	0 1 1 2 2 3 3 0 0 2 1 3
	6 10
	0 1 0 2 1 2 1 3 1 4 2 3 2 4 3 4 3 5 4 5

	- Result

	1
	3
	4
*/
int main()
{
	// 입력
	int test_case;
	scanf("%d", &test_case);
	for (int i = 0; i < test_case; i++)
	{
		int relations[MAX_FRIEND_COUNT][MAX_FRIEND_COUNT] = { 0, };
		int visited[MAX_FRIEND_COUNT] = { 0, };
		int n, m;
		scanf("%d%d", &n, &m);
		for (int j = 0; j < m; j++)
		{
			int f1, f2;
			scanf("%d%d", &f1, &f2);
			relations[f1][f2] = 1;
			relations[f2][f1] = 1;
		}

		// 계산
		int result = get_group_count(relations, visited, 0, 0, n);

		// 출력
		printf("%d\n", result);
	}

	return 0;
}