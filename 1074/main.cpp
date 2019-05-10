#include <stdio.h>

typedef struct Area
{
	int r;
	int c;
} Area;

Area areas[] = { {0, 0}, {0, 1}, {1, 0}, {1, 1} };

int main()
{
	int result = 0;
	int n, r, c;
	
	// �Է�
	scanf("%d%d%d", &n, &r, &c);

	// ���
	for (int i = n - 1; i >= 0; i--)
	{
		result *= 4;
		// 2 ^ i
		int sub_n = 1 << i;
		// Z index ���ϱ� (0, 1, 2, 3)
		int area_index = (r / sub_n) * 2 + (c / sub_n);
		// ��� ����
		result += area_index;
		// r, c ����
		r -= sub_n * areas[area_index].r;
		c -= sub_n * areas[area_index].c;
	}

	printf("%d\n", result);

	return 0;
}