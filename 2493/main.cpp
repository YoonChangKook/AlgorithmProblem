#include <stdio.h>

#define MAX_TOWER_COUNT 500000

int n;
int towers[MAX_TOWER_COUNT];
int ans[MAX_TOWER_COUNT];
// 타워의 인덱스를 저장할 스택
int stack[MAX_TOWER_COUNT];
int stack_top = -1;

int main()
{
	// 입력
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
		scanf("%d", &towers[i]);

	// 계산 (오른쪽 끝부터)
	for (int i = n - 1; i >= 0; i--)
	{
		// 스택에는 항상 작은것만 쌓이게 되고, 큰 값 만나면 비운다.
		while (stack_top >= 0 && towers[i] > towers[stack[stack_top]])
			ans[stack[stack_top--]] = i + 1;
		stack[++stack_top] = i;
	}

	// 출력
	for (int i = 0; i < n; i++)
		printf("%d ", ans[i]);

	return 0;
}