#include <stdio.h>
#include <queue>
#include <vector>

#define MAX 100

using namespace std;

typedef pair<int, int> Pair;
Pair operator+(const Pair& p1, const Pair& p2)
{
	return { p1.first + p2.first, p1.second + p2.second };
}

int n;
int map[MAX][MAX];
int max_value = 0;
Pair dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int CalcAreaNum(int height);

int main()
{
	// 입력
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			scanf("%d", &map[i][j]);
			if (map[i][j] > max_value)
				max_value = map[i][j];
		}
	}

	// 계산
	int max_area_num = 0;
	for (int i = 0; i < max_value; i++)
	{
		int area_num = CalcAreaNum(i);
		if (max_area_num <= area_num)
			max_area_num = area_num;
	}

	// 출력
	printf("%d\n", max_area_num);

	return 0;
}

int CalcAreaNum(int height)
{
	int area_num = 0;
	int visited[MAX][MAX] = { 0, };
	
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			// 이미 검사했거나 높이가 낮으면 통과
			if (visited[i][j] != 0 || map[i][j] <= height)
				continue;

			queue<Pair> calc_queue;
			visited[i][j] = 1;
			calc_queue.push({ i, j });
			while (!calc_queue.empty())
			{
				Pair pos = calc_queue.front();
				calc_queue.pop();
				for (int k = 0; k < 4; k++)
				{
					Pair next_pos = pos + dir[k];
					if (0 <= next_pos.first && next_pos.first < n &&
						0 <= next_pos.second && next_pos.second < n &&
						visited[next_pos.first][next_pos.second] == 0 &&
						map[next_pos.first][next_pos.second] > height)
					{
						calc_queue.push(next_pos);
						visited[next_pos.first][next_pos.second] = 1;
					}
				}
			}

			area_num++;
		}
	}

	return area_num;
}