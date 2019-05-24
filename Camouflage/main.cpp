#include <stdio.h>
#include <string>
#include <vector>
#include <map>

#define MAX_CLOTHE_COUNT 30

using namespace std;

// counts ���� ��ҵ鿡�� ����(nCr) �� ���� ����� �� ��� ���� �� ��ȯ
int combination(int counts[MAX_CLOTHE_COUNT], int n, int r, int current = 1)
{
	// n�� �� n�� ����
	if (n == r)
	{
		for (int i = 0; i < n; i++)
			current *= counts[i];
		return current;
	}
	
	// �ϳ��� ���� ���� �� ���� ���� ��ȯ
	if (r == 0)
		return current;

	// nCr = n-1Cr-1 + n-1Cr
	return combination(counts, n - 1, r - 1, current * counts[n - 1]) + combination(counts, n - 1, r, current);
}

int solution(vector<vector<string>> clothes) {
	int answer = 0;

	// �з�
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
	
	// ���� ����� ��
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