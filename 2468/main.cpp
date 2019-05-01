#include <stdio.h>
#include <queue>
#include <vector>

#define MAX 100

using namespace std;

int n;
int map[MAX][MAX];
int max_value = 0;
int dir_x[4] = { 1, 0, -1, 0 };
int dir_y[4] = { 0, 1, 0, -1 };

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
		else
			break;
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

			queue<pair<int, int>> calc_queue;
			visited[i][j] = 1;
			calc_queue.push({ i, j });
			while (!calc_queue.empty())
			{
				pair<int, int> pos = calc_queue.front();
				calc_queue.pop();
				for (int k = 0; k < 4; k++)
				{
					int next_x = pos.second + dir_x[k];
					int next_y = pos.first + dir_y[k];
					if (0 <= next_y && next_y < n &&
						0 <= next_x && next_x < n &&
						visited[next_y][next_x] == 0 &&
						map[next_y][next_x] > height)
					{
						calc_queue.push({ next_y, next_x });
						visited[next_y][next_x] = 1;
					}
				}
			}

			area_num++;
		}
	}

	return area_num;
}