#include <stdio.h>

#define MAX_TOWER_COUNT 500000

int n;
int towers[MAX_TOWER_COUNT];
int ans[MAX_TOWER_COUNT];
// Ÿ���� �ε����� ������ ����
int stack[MAX_TOWER_COUNT];
int stack_top = -1;

int main()
{
	// �Է�
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &towers[i]);

	// ��� (������ ������)
	for (int i = n - 1; i >= 0; i--)
	{
		// ���ÿ��� �׻� �����͸� ���̰� �ǰ�, ū �� ������ ����.
		while (stack_top >= 0 && towers[i] > towers[stack[stack_top]])
			ans[stack[stack_top--]] = i + 1;
		stack[++stack_top] = i;
	}

	// ���
	for (int i = 0; i < n; i++)
		printf("%d ", ans[i]);

	return 0;
}