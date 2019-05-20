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
	// null ���ڱ��� ������ ���� (������ ��ġ)
	if (target_str[0] == '\0')
		return true;

	// ù���ڰ� �������� Ȯ��
	if (target_str[0] != map[pos.y][pos.x])
		return false;

	// 8���� ��ȸ
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

	// �Է�
	scanf("%s", word);
	for (int i = 0; i < SIZE; i++)
		scanf("%s", map[i]);
	scanf("%d%d", &start_pos.x, &start_pos.y);

	// ���
	bool result = has_word(word, start_pos);

	// ���
	printf("%s\n", result ? "true" : "false");

	return 0;
}