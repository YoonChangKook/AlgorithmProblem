#include <stdio.h>

#define SIZE 5

typedef struct Position
{
	int x;
	int y;

	Position operator + (const Position& other) const
	{
		return { x + other.x, y + other.y };
	}
} Position;

Position dirs[8] = { {1, 0}, {1, 1}, {0, 1}, {-1, 1}, {-1, 0}, {-1, -1}, {0, -1}, {1, -1} };

char word[SIZE * SIZE + 1];
char map[SIZE][SIZE + 1];
int word_count = 0;

int strlen(const char* const str)
{
	int i = 0;
	for (int i = 0; ; i++)
		if (str[i] == '\0')
			return i;
}

void strcpy(char* dest, const char* const src)
{
	int src_len = strlen(src);
	for (int i = 0; i < src_len; i++)
		dest[i] = src[i];
	dest[src_len] = '\0';
}

int strcmp(const char* const str1, const char* const str2)
{
	for (int i = 0; str1[i] != '\0'; i++)
	{
		if (str1[i] != str2[i])
			return str1[i] < str2[i];
	}

	return 0;
}

bool has_word(const char* target_str, Position pos)
{
	// null 문자까지 갔으면 성공 (끝까지 일치)
	if (target_str[0] == '\0')
		return true;

	// 첫글자가 동일한지 확인
	if (target_str[0] != map[pos.y][pos.x])
		return false;

	// 8방향 순회
	for (int i = 0; i < 8; i++)
	{
		Position new_pos = pos + dirs[i];
		if (new_pos.x < 0 || SIZE <= new_pos.x || new_pos.y < 0 || SIZE <= new_pos.y)
			continue;

		if (has_word(target_str + 1, new_pos))
			return true;
	}

	return false;
}

int main()
{
	Position start_pos;

	// 입력
	scanf("%s", word);
	for (int i = 0; i < SIZE; i++)
		scanf("%s", map[i]);
	scanf("%d%d", &start_pos.x, &start_pos.y);

	// 계산
	bool result = has_word(word, start_pos);

	// 출력
	printf("%s\n", result ? "true" : "false");

	return 0;
}