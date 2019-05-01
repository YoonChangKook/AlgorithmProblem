#include <stdio.h>
#include <vector>
#define MAX 100

enum Direction
{
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};

typedef struct Shark
{
	int r_;
	int c_;
	int speed_;
	Direction dir_;
	int size_;
} Shark;

int row, column, shark_count;
std::vector<Shark> sharks;

int CatchAShark(int hunter_pos);
void MoveSharks();
void print();

int main()
{
	int r, c, s, d, z;
	int result = 0;

	// 입력
	scanf("%d%d%d", &row, &column, &shark_count);
	for (int i = 0; i < shark_count; i++)
	{
		scanf("%d%d%d%d%d", &r, &c, &s, &d, &z);
		sharks.push_back({ r - 1, c - 1, s, (Direction)d, z });
	}

	// 계산
	for (int i = 0; i < column; i++)
	{
		result += CatchAShark(i);
		MoveSharks();
		print();
	}

	// 출력
	printf("%d\n", result);

	return 0;
}

int CatchAShark(int hunter_pos)
{
	int most_up_pos = MAX;
	int target_shark_index = -1;

	for (int i = 0; i < sharks.size(); i++)
	{
		if (sharks[i].c_ == hunter_pos)
		{
			if (most_up_pos > sharks[i].r_)
			{
				target_shark_index = i;
				most_up_pos = sharks[i].r_;
			}
		}
	}

	if (target_shark_index >= 0)
	{
		int shark_size = sharks[target_shark_index].size_;
		sharks.erase(sharks.begin() + target_shark_index);

		return shark_size;
	}
	else
		return 0;
}

void MoveSharks()
{
	std::vector<Shark> new_sharks;

	for (int i = 0; i < sharks.size(); i++)
	{
		Shark& target_shark = sharks[i];
		int& target_pos = target_shark.dir_ == Direction::UP || target_shark.dir_ == Direction::DOWN ? target_shark.r_ : target_shark.c_;

		// 다음 좌표 계산
		switch (target_shark.dir_)
		{
		case Direction::UP:
		{
			int next_cell = target_shark.r_ - target_shark.speed_ + 1;
			if (next_cell > 0)
			{
				target_shark.r_ = next_cell - 1;
				break;
			}

			Direction next_dir = (next_cell / (row - 1)) % 2 == 0 ? Direction::DOWN : Direction::UP;
			int start_pos = next_dir == Direction::UP ? row - 1 : 0;
			int next_pos = start_pos > 0 ? start_pos + next_cell % (row - 1) - 1 : start_pos - next_cell % (row - 1) + 1;

			target_shark.r_ = next_pos;
			target_shark.dir_ = next_dir;

			break;
		}
		case Direction::DOWN:
		{
			int next_cell = target_shark.r_ + target_shark.speed_ - 1;
			if (next_cell < row - 1)
			{
				target_shark.r_ = next_cell + 1;
				break;
			}

			Direction next_dir = (next_cell / (row - 1)) % 2 == 0 ? Direction::DOWN : Direction::UP;
			int start_pos = next_dir == Direction::UP ? row - 1 : 0;
			int next_pos = start_pos > 0 ? start_pos - next_cell % (row - 1) - 1 : start_pos + next_cell % (row - 1) + 1;

			target_shark.r_ = next_pos;
			target_shark.dir_ = next_dir;

			break;
		}
		case Direction::RIGHT:
		{
			int next_cell = target_shark.c_ + target_shark.speed_ - 1;
			if (next_cell < column - 1)
			{
				target_shark.c_ = next_cell + 1;
				break;
			}

			Direction next_dir = (next_cell / (column - 1)) % 2 == 0 ? Direction::RIGHT : Direction::LEFT;
			int start_pos = next_dir == Direction::LEFT ? column - 1 : 0;
			int next_pos = start_pos > 0 ? start_pos - next_cell % (column - 1) - 1 : start_pos + next_cell % (column - 1) + 1;

			target_shark.c_ = next_pos;
			target_shark.dir_ = next_dir;

			break;
		}
		case Direction::LEFT:
		{
			int next_cell = target_shark.c_ - target_shark.speed_ + 1;
			if (next_cell > 0)
			{
				target_shark.c_ = next_cell - 1;
				break;
			}

			Direction next_dir = (next_cell / (column - 1)) % 2 == 0 ? Direction::RIGHT : Direction::LEFT;
			int start_pos = next_dir == Direction::LEFT ? column - 1 : 0;
			int next_pos = start_pos > 0 ? start_pos + next_cell % (column - 1) - 1 : start_pos - next_cell % (column - 1) + 1;

			target_shark.c_ = next_pos;
			target_shark.dir_ = next_dir;

			break;
		}
		}

		// 겹치는지 확인
		bool can_insert = true;
		for (int j = 0; j < new_sharks.size(); j++)
		{
			if (new_sharks[j].r_ == target_shark.r_ && new_sharks[j].c_ == target_shark.c_)
			{
				if (target_shark.size_ > new_sharks[j].size_)
					new_sharks.erase(new_sharks.begin() + j);
				else
					can_insert = false;

				break;
			}
		}

		if (can_insert)
			new_sharks.push_back(target_shark);
	}

	sharks = new_sharks;
}

void print()
{
	int temp_map[MAX][MAX] = { 0, };

	for (int i = 0; i < sharks.size(); i++)
		temp_map[sharks[i].r_][sharks[i].c_] = i + 1;

	printf("\n");
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
			printf("%d ", temp_map[i][j]);

		printf("\n");
	}
	printf("\n");
}