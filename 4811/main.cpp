#include <stdio.h>
#include <memory.h>

int calc_pill(int index, int full_pill_count, int half_pill_count, char str[31])
{
	if (full_pill_count == 0 && half_pill_count == 0)
	{
		str[index] = '\0';
		printf("%s\n", str);
		return 1;
	}
	else
	{
		int result = 0;

		if (full_pill_count > 0)
		{
			char new_str[31];
			memcpy(new_str, str, sizeof(char) * 31);
			new_str[index] = 'W';
			result += calc_pill(index + 1, full_pill_count - 1, half_pill_count + 1, new_str);
		}
		if (half_pill_count > 0)
		{
			char new_str[31];
			memcpy(new_str, str, sizeof(char) * 31);
			new_str[index] = 'H';
			result += calc_pill(index + 1, full_pill_count, half_pill_count - 1, new_str);
		}

		return result;
	}
}

int main()
{
	int n;

	scanf("%d", &n);

	char str[31];
	printf("%d\n", calc_pill(0, n, 0, str));

	return 0;
}