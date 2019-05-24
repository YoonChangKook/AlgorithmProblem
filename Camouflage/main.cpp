#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#define MAX_CLOTHE_COUNT 30

using namespace std;

// counts 안의 요소들에서 조합(nCr) 로 나온 경우의 수 모두 더한 것 반환
int combination(int counts[MAX_CLOTHE_COUNT], int n, int r, int current = 1)
{
	// n개 중 n개 선택
	if (n == r)
	{
		for (int i = 0; i < n; i++)
			current *= counts[i];
		return current;
	}
	
	// 하나도 선택 안할 때 현재 상태 반환
	if (r == 0)
		return current;

	// nCr = n-1Cr-1 + n-1Cr
	return combination(counts, n - 1, r - 1, current * counts[n - 1]) + combination(counts, n - 1, r, current);
}

int solution(vector<vector<string>> clothes) {
	int answer = 0;

	// 분류
	map<string, int> count_by_type;
	int counts[MAX_CLOTHE_COUNT] = { 0, };
	int i;
	for (i = 0; i < clothes.size(); i++)
	{
		if (count_by_type.find(clothes[i][1]) == count_by_type.end())
			count_by_type[clothes[i][1]] = 0;

		count_by_type[clothes[i][1]]++;
	}
	i = 0;
	for (auto pair : count_by_type)
		counts[i++] = pair.second;
	
	// 조합 경우의 수
	for (int i = 1; i <= count_by_type.size(); i++)
		answer += combination(counts, count_by_type.size(), i);

	return answer;
}

int main()
{
	//vector<vector<string>> param = { { "yellow_hat", "headgear" }, { "blue_sunglasses", "eyewear" }, { "green_turban", "headgear" } };
	vector<vector<string>> param = { {"crow_mask", "face"}, {"blue_sunglasses", "face"}, {"smoky_makeup", "face"} };

	printf("%d\n", solution(param));

	return 0;
}