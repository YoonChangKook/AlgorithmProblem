#include <stdio.h>

#define MAX_TEST_CASE 100
#define MAX_MAP_WIDTH 1001

template <class T>
class queue
{
private:
	T* arr;
	int capacity;
	int count;
	int start;
	int rear;

public:
	queue()
		: capacity(100), count(0), start(0), rear(0)
	{
		arr = new T[capacity];
	}

	~queue()
	{
		delete[] arr;
	}

	void push_back(const T& item)
	{
		if (capacity <= count)
			reallocate(capacity * 2);

		arr[rear] = item;
		rear = (rear + 1) % capacity;
		count++;
	}

	const T& front() const
	{
		return arr[this->start];
	}

	void pop()
	{
		start = (start + 1) % capacity;
		count--;
	}

	int size() const
	{
		return count;
	}

	bool empty() const
	{
		return start == rear;
	}

private:
	void reallocate(int new_capacity)
	{
		T* new_arr = new T[new_capacity];
		for (int i = 0; i < count; i++)
			new_arr[i] = arr[(start + i) % capacity];
		delete[] arr;

		arr = new_arr;
		capacity = new_capacity;
		start = 0;
		rear = count;
	}
};

enum CELL {
	EMPTY = '.',
	WALL = '#',
	START = '@',
	FIRE = '*'
};

typedef struct Pos {
	int x;
	int y;
	int seconds;

	Pos operator + (const Pos& other)
	{
		return { x + other.x, y + other.y, seconds + other.seconds };
	}
} Pos;

int test_case;
int w, h;
Pos start_pos;
Pos dirs[] = { {1, 0, 1}, {0, 1, 1}, {-1, 0, 1}, {0, -1, 1} };
char map[MAX_MAP_WIDTH][MAX_MAP_WIDTH] = { 0, };

void print()
{
	printf("\n");
	for (int i = 0; i < h; i++)
	{
		for (int j = 0; j < w; j++)
			printf("%c", map[i][j]);
		printf("\n");
	}
}

int calc_escape_seconds(queue<Pos>& path_finder, queue<Pos>& fires)
{
	while (!path_finder.empty())
	{
		// 불 옮기기
		int fire_size = fires.size();
		for (int i = 0; i < fire_size; i++)
		{
			Pos fire_front = fires.front();
			fires.pop();
			for (int j = 0; j < 4; j++)
			{
				Pos next_fire = fire_front + dirs[j];

				if (next_fire.x < 0 || w <= next_fire.x ||
					next_fire.y < 0 || h <= next_fire.y)
					continue;

				if (map[next_fire.y][next_fire.x] == CELL::EMPTY || 
					map[next_fire.y][next_fire.x] == CELL::START)
				{
					map[next_fire.y][next_fire.x] = CELL::FIRE;
					fires.push_back(next_fire);
				}
			}
		}

		// 길 찾기
		int path_size = path_finder.size();
		for (int i = 0; i < path_size; i++)
		{
			Pos front = path_finder.front();
			path_finder.pop();
			for (int i = 0; i < 4; i++)
			{
				Pos next = front + dirs[i];

				// 탈출 처리
				if (next.x < 0 || w <= next.x || next.y < 0 || h <= next.y)
					return next.seconds;

				if (map[next.y][next.x] == CELL::EMPTY)
				{
					map[next.y][next.x] = CELL::START;
					path_finder.push_back(next);
				}
			}
		}
	}
	
	return -1;
}

int main()
{
	int result[MAX_TEST_CASE];

	// 입력
	scanf("%d", &test_case);
	for (int i = 0; i < test_case; i++)
	{
		queue<Pos> path_finder;
		queue<Pos> fires;

		scanf("%d%d", &w, &h);
		for (int j = 0; j < h; j++)
		{
			scanf("%s", &map[j]);
			for (int k = 0; k < w; k++)
			{
				switch (map[j][k])
				{
				case CELL::START:
					path_finder.push_back({ k, j, 0 });
					break;

				case CELL::FIRE:
					fires.push_back({ k, j, 0 });
					break;
				}
			}
		}

		// 계산
		result[i] = calc_escape_seconds(path_finder, fires);
	}

	// 출력
	for (int i = 0; i < test_case; i++)
	{
		// 출력
		if (result[i] < 0)
			printf("IMPOSSIBLE\n");
		else
			printf("%d\n", result[i]);
	}

	return 0;
}