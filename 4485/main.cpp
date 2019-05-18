#include <stdio.h>

#define INF 0x7fffffff
#define MAX_CAVE_SIZE 125

template <class T>
class vector
{
private:
	T* arr;
	int capacity;
	int count;

public:
	vector()
		: capacity(MAX_CAVE_SIZE), count(0)
	{
		arr = new T[capacity];
	}

	vector(int size)
		: capacity(size), count(0)
	{
		arr = new T[capacity];
	}

	vector(int size, T init_value)
		: capacity(size), count(size)
	{
		arr = new T[capacity];
		for (int i = 0; i < count; i++)
			arr[i] = init_value;
	}

	~vector()
	{
		delete[] arr;
	}

	vector(const vector<T>& other)
	{
		arr = new T[other.capacity];
		for (int i = 0; i < other.capacity; i++)
			arr[i] = other.arr[i];
		capacity = other.capacity;
		count = other.count;
	}

	void push_back(const T& item)
	{
		if (capacity <= count)
			reallocate(capacity * 2);

		arr[count++] = item;
	}

	T pop_back()
	{
		return arr[--count];
	}

	T& operator[] (int index)
	{
		return arr[index];
	}

	T operator[] (int index) const
	{
		return arr[index];
	}

	int size() const
	{
		return count;
	}

	void resize(int size)
	{
		while (capacity < size)
			reallocate(capacity * 2);

		count = size;
	}

private:
	void reallocate(int new_capacity)
	{
		T* temp_arr = new T[new_capacity];
		for (int i = 0; i < capacity; i++)
			temp_arr[i] = arr[i];
		delete[] arr;

		arr = temp_arr;
		capacity = new_capacity;
	}
};

template <class T>
class priority_queue
{
private:
	vector<T> arr;

public:
	void push(const T& item)
	{
		arr.push_back(item);
		quicksort(arr, 0, arr.size() - 1);
	}

	T top() const
	{
		return arr[arr.size() - 1];
	}

	void pop()
	{
		arr.pop_back();
	}

	int size() const
	{
		return arr.size();
	}

	bool empty() const
	{
		return arr.size() == 0;
	}

private:
	void quicksort(vector<T>& arr, int start, int end)
	{
		int pivot = start;
		int left = start, right = end;

		while (left < right)
		{
			while (left < right && arr[right] <= arr[pivot]) right--;
			while (left < right && arr[pivot] <= arr[left]) left++;
			swap(arr[left], arr[right]);
		}
		swap(arr[pivot], arr[left]);

		if (start < left)
			quicksort(arr, start, left - 1);
		if (right < end)
			quicksort(arr, left + 1, end);
	}

	void swap(T& item1, T& item2)
	{
		T temp = item1;
		item1 = item2;
		item2 = temp;
	}
};

typedef struct Vertex
{
	int x;
	int y;
	int weight;

	bool operator <= (const Vertex& other)
	{
		return weight <= other.weight;
	}
} Vertex;

typedef struct {
	int x;
	int y;
} Direction;

int n;
int graph[MAX_CAVE_SIZE][MAX_CAVE_SIZE] = { 0, };
int result[MAX_CAVE_SIZE][MAX_CAVE_SIZE] = { 0, };
Direction dirs[] = { { 1, 0 }, { 0, 1 }, { -1, 0 }, { 0, -1 } };

int find_min_cost()
{
	priority_queue<Vertex> queue;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++)
			result[i][j] = INF;
	result[0][0] = graph[0][0];
	queue.push({ 0, 0, graph[0][0] });

	while (!queue.empty())
	{
		Vertex top = queue.top();
		queue.pop();

		if (top.weight != result[top.y][top.x])
			continue;

		for (int i = 0; i < 4; i++)
		{
			Vertex next = { top.x + dirs[i].x, top.y + dirs[i].y, 0 };
			if (next.x < 0 || n <= next.x || next.y < 0 || n <= next.y)
				continue;
			next.weight = graph[next.y][next.x];

			// 결과 찾으면 리턴
			if (next.y == n - 1 && next.x == n - 1)
				return next.weight + top.weight;

			if (next.weight + top.weight < result[next.y][next.x])
			{
				result[next.y][next.x] = next.weight + top.weight;
				queue.push({ next.x, next.y, result[next.y][next.x] });
			}
		}
	}

	return -1;
}

int main()
{
	// 입력
	for(int problem_num = 1; ; problem_num++)
	{
		scanf("%d", &n);
		if (n == 0)
			return 0;

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				scanf("%d", &graph[i][j]);

		// 계산
		int result = find_min_cost();

		// 출력
		printf("Problem %d: %d\n", problem_num, result);
	}

	return 0;
}