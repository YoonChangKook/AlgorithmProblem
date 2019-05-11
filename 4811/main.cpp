#include <stdio.h>

#define MAX_N 30

int main()
{
	while (true)
	{
		int n;
		long long num_counts[MAX_N] = { 0, };
		long long result = 0;
		num_counts[0] = 1L; num_counts[1] = 1L;

		// �Է�
		scanf("%d", &n);
		if (n == 0)
			break;

		// ���
		for (int i = 2; i < n - 1; i++) // �� ���� �� ����
			for (int j = 0; j < i; j++)
				num_counts[j + 1] += num_counts[j];
		for (int i = 0; i < n - 1; i++) // ���� ������ ���� ����
			result += num_counts[i] * (n - i);

		// ���
		printf("%lld\n", result == 0 ? 1 : result);
	}

	return 0;
}