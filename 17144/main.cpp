#include <stdio.h>
#include <string.h>

#define MAX 50
#define MIN_SPREAD_VALUE 5

typedef struct Cleaner
{
	int x;
	int y;
} Cleaner;

int map[MAX][MAX];
int r, c, t;
Cleaner top;
Cleaner bottom;

void calc_spread();
void calc_top_wind();
void calc_bottom_wind();
void print();

int main()
{
	int result = 0;

	//입력
	bool isTopInserted = false;
	scanf("%d%d%d", &r, &c, &t);
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			scanf("%d", &map[i][j]);

			// 공기 청정기
			if (map[i][j] == -1)
			{
				if (!isTopInserted)
				{
					top = { j, i };
					isTopInserted = true;
				}
				else
					bottom = { j, i };
			}
		}
	}

	// 시뮬레이션
	for (int i = 0; i < t; i++)
	{
		calc_spread();
		calc_top_wind();
		calc_bottom_wind();
	}

	// 계산
	for (int i = 0; i < r; i++)
		for (int j = 0; j < c; j++)
			if (map[i][j] > 0)
				result += map[i][j];

	// 출력
	printf("%d\n", result);
}

void calc_spread()
{
	int copy_map[MAX][MAX] = { 0, };
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			if (map[i][j] > 0)
			{
				int spread_count = 0;
				if (i > 0 && map[i - 1][j] >= 0)
				{
					copy_map[i - 1][j] += map[i][j] / 5;
					spread_count++;
				}
				if (j > 0 && map[i][j - 1] >= 0)
				{
					copy_map[i][j - 1] += map[i][j] / 5;
					spread_count++;
				}
				if (i < r - 1 && map[i + 1][j] >= 0)
				{
					copy_map[i + 1][j] += map[i][j] / 5;
					spread_count++;
				}
				if (j < c - 1 && map[i][j + 1] >= 0)
				{
					copy_map[i][j + 1] += map[i][j] / 5;
					spread_count++;
				}
				copy_map[i][j] += map[i][j] - (map[i][j] / 5) * spread_count;
			}
			else if (map[i][j] < 0)
				copy_map[i][j] = -1;
		}
	}
	memcpy(map, copy_map, sizeof(int) * MAX * MAX);
}

void calc_top_wind()
{
	int temp = map[top.y][top.x + 1];
	map[top.y][top.x + 1] = 0;
	for (int i = 1; i < c - 1; i++)
	{
		int temp2 = map[top.y][i + 1];
		map[top.y][i + 1] = temp;
		temp = temp2;
	}
	for (int i = top.y; i > 0; i--)
	{
		int temp2 = map[i - 1][c - 1];
		map[i - 1][c - 1] = temp;
		temp = temp2;
	}
	for (int i = c - 1; i > 0; i--)
	{
		int temp2 = map[0][i - 1];
		map[0][i - 1] = temp;
		temp = temp2;
	}
	for (int i = 0; i < top.y - 1; i++)
	{
		int temp2 = map[i + 1][0];
		map[i + 1][0] = temp;
		temp = temp2;
	}
}

void calc_bottom_wind()
{
	int temp = map[bottom.y][bottom.x + 1];
	map[bottom.y][bottom.x + 1] = 0;
	for (int i = 1; i < c - 1; i++)
	{
		int temp2 = map[bottom.y][i + 1];
		map[bottom.y][i + 1] = temp;
		temp = temp2;
	}
	for (int i = bottom.y; i < r - 1; i++)
	{
		int temp2 = map[i + 1][c - 1];
		map[i + 1][c - 1] = temp;
		temp = temp2;
	}
	for (int i = c - 1; i > 0; i--)
	{
		int temp2 = map[r - 1][i - 1];
		map[r - 1][i - 1] = temp;
		temp = temp2;
	}
	for (int i = r - 1; i > bottom.y + 1; i--)
	{
		int temp2 = map[i - 1][0];
		map[i - 1][0] = temp;
		temp = temp2;
	}
}

void print()
{
	// 출력
	printf("\n");
	for (int i = 0; i < r; i++)
	{
		for (int j = 0; j < c; j++)
		{
			printf("%d ", map[i][j]);
		}
		printf("\n");
	}
}