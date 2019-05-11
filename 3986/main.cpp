#include <stdio.h>

#define MAX_BUF_SIZE 1000100
#define MAX_WORD_LENGTH 100001
#define MAX_WORDS_COUNT 100

char buf[MAX_BUF_SIZE] = { 0, };
char* words[MAX_WORDS_COUNT];
int word_lens[MAX_WORDS_COUNT];
char stack[MAX_WORD_LENGTH];
int stack_top = -1;

int strlen(const char* str)
{
	int i;
	for (i = 0; str[i] != '\0'; i++);
	return i;
}

int main()
{
	int n, result = 0;
	char* buf_ptr = buf;

	// 입력
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", buf_ptr);
		words[i] = buf_ptr;
		word_lens[i] = strlen(buf_ptr);
		buf_ptr += (word_lens[i] + 1);
	}

	// 계산
	for (int i = 0; i < n; i++)
	{
		stack_top = -1;

		for (int j = 0; j < word_lens[i]; j++)
		{
			if (stack_top < 0 || stack[stack_top] != words[i][j])
				stack[++stack_top] = words[i][j];
			else
				stack_top--;
		}

		if (stack_top < 0)
			result++;
	}

	// 출력
	printf("%d\n", result);

	return 0;
}