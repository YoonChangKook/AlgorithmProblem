#include <stdio.h>

#define MAX_N 30

int n;
long long dp[MAX_N] = { 1LL, };

int main()
{
	// ��� (īŻ�� ��, Ȧ�γ�� ����)
	for (int i = 1; i < 30; i++)
		dp[i] = dp[i - 1] * (4 * i + 2) / (i + 2);
	// ���
	for (; scanf("%d", &n); printf("%lld\n", dp[n - 1]))
		if (!n)
			return 0;
}