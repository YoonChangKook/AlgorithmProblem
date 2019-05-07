#include <stdio.h>
#include <algorithm>
#include <functional>
#include <vector>

#define MAX 100

using namespace std;

// 좌표
typedef pair<int, int> Pos;
Pos operator+(const Pos& p1, const Pos& p2)
{
	return{ p1.first + p2.first, p1.second + p2.second };
}
// 높이, 좌표 쌍
typedef pair<int, Pos> Height;

int n;
vector<Height> heights;
int max_value = 0;
Pos dir[4] = { {0, 1}, {1, 0}, {0, -1}, {-1, 0} };

int uf_find(int group[], int u)
{
	if (u == group[u]) return u;
	return group[u] = uf_find(group, group[u]);
}

bool uf_union(int group[], int u, int v)
{
	u = uf_find(group, u);
	v = uf_find(group, v);

	if (u == v)
		return false;

	group[u] = v;

	return true;
}

int getIdx(const Pos& pos)
{
	return pos.first * n + pos.second;
}

bool isValidPos(const Pos& pos)
{
	return 0 <= pos.first && pos.first < n && 0 <= pos.second && pos.second < n;
}

int calcAreaNum()
{
	int group[MAX * MAX]; // disjoint set으로 나눈 그룹
	bool available[MAX * MAX] = { false, }; // 해당 좌표가 기준 높이 이상인지 체크
	int group_count = 0, max_group_count = 0;

	// 초기화
	for (int i = 0; i < n * n; i++)
		group[i] = i;

	// 그룹 계산
	for (int i = 0, next; i < heights.size() - 1; i = next)
	{
		// 다음 높이 인덱스 찾기
		for (next = i; next < heights.size() && heights[i].first == heights[next].first; next++);
		for (int j = i; j < next; j++)
		{
			available[getIdx(heights[j].second)] = true;
			group_count++;
			for (int k = 0; k < 4; k++)
			{
				Pos next_pos = heights[j].second + dir[k];
				if (isValidPos(next_pos) && available[getIdx(next_pos)])
					group_count -= uf_union(group, getIdx(heights[j].second), getIdx(next_pos));
			}
		}

		if (group_count > max_group_count)
			max_group_count = group_count;
	}

	return max_group_count;
}

int main()
{
	// 입력
	scanf("%d", &n);
	Pos pos; int h;
	for (pos.first = 0; pos.first < n; pos.first++)
	{
		for (pos.second = 0; pos.second < n; pos.second++)
		{
			scanf("%d", &h);
			heights.push_back({ h, pos });
		}
	}

	// 높이 순으로 좌표 정렬
	sort(heights.begin(), heights.end(), greater<Height>());

	// 계산
	int max_area_num = calcAreaNum();

	// 출력
	printf("%d\n", max_area_num);

	return 0;
}