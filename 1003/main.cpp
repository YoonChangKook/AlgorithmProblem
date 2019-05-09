#include <stdio.h>

int main()
{
	int zero_counts[41] = { 0, };
	int one_counts[41] = { 0, };

	zero_counts[0] = 1;
	one_counts[1] = 1;

	// 입력
	int T;
	scanf("%d", &T);
	for (int i = 0; i < T; i++)
	{
		int N;
		scanf("%d", &N);
		// 계산
		for (int j = 2; j <= N; j++)
		{
			zero_counts[j] = zero_counts[j - 1] + zero_counts[j - 2];
			one_counts[j] = one_counts[j - 1] + one_counts[j - 2];
		}

		printf("%d %d\n", zero_counts[N], one_counts[N]);
	}

	return 0;
}