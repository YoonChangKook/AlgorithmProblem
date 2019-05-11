#include <stdio.h>

#define MAX_COMMAND_COUNT 10000

int arr[MAX_COMMAND_COUNT];
int top = -1;

bool is_equal(const char* str1, const char* str2)
{
	int i = 0;
	while (str1[i] != '\0' && str2[i] != '\0')
	{
		if (str1[i] != str2[i])
			return false;
		i++;
	}

	// 마지막 둘다 null인지 비교
	return str1[i] == str2[i];
}

int main()
{
	int n;
	char command[10];

	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", command);

		if (is_equal(command, "push"))
		{
			int push_num;
			scanf("%d", &push_num);
			arr[++top] = push_num;
		}
		else if (is_equal(command, "pop"))
		{
			printf("%d\n", top < 0 ? -1 : arr[top--]);
		}
		else if (is_equal(command, "size"))
		{
			printf("%d\n", top + 1);
		}
		else if (is_equal(command, "empty"))
		{
			printf("%d\n", top < 0 ? 1 : 0);
		}
		else if (is_equal(command, "top"))
		{
			printf("%d\n", top < 0 ? -1 : arr[top]);
		}
	}

	return 0;
}