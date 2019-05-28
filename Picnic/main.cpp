#include <stdio.h>

#define MAX_FRIEND_COUNT 10
#define MAX_RELATIONSHIP_COUNT 45

template <class T>
class vector
{
private:
	T* arr;
	int capacity;
	int count;

public:
	vector()
		: capacity(MAX_FRIEND_COUNT), count(0)
	{
		arr = new T[capacity];
	}

	~vector()
	{
		delete[] arr;
	}

	vector(const vector<T>& other)
		: capacity(other.capacity), count(other.count)
	{
		arr = new T[capacity];
		for (int i = 0; i < count; i++)
			arr[i] = other.arr[i];
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

	const T& operator[] (int index) const
	{
		return arr[index];
	}

	int size() const
	{
		return count;
	}

	bool contains(const T& item) const
	{
		for (int i = 0; i < count; i++)
			if (arr[i] == item)
				return true;

		return false;
	}

private:
	void reallocate(int new_capacity)
	{
		T* new_arr = new T[new_capacity];
		for (int i = 0; i < count; i++)
			new_arr[i] = arr[i];
		delete[] arr;

		arr = new_arr;
		capacity = new_capacity;
	}
};

typedef struct Friend {
	int f1;
	int f2;
} Friend;

int get_group_count(const int relations[MAX_FRIEND_COUNT][MAX_FRIEND_COUNT], int visited[MAX_FRIEND_COUNT], int current_pair_count, int start, int n)
{
	int result = 0;

	if (current_pair_count == n / 2)
		return 1;

	for (int i = start; i < n; i++)
	{
		for (int j = i + 1; j < n; j++)
		{
			if (!visited[i] && !visited[j] && relations[i][j])
			{
				visited[i] = visited[j] = true;
				result += get_group_count(relations, visited, current_pair_count + 1, i + 1, n);
				visited[i] = visited[j] = false;
			}		
		}
	}

	return result;
}

int main()
{
	// 입력
	int test_case;
	scanf("%d", &test_case);
	for (int i = 0; i < test_case; i++)
	{
		int relations[MAX_FRIEND_COUNT][MAX_FRIEND_COUNT] = { 0, };
		int visited[MAX_FRIEND_COUNT] = { 0, };
		int n, m;
		scanf("%d%d", &n, &m);
		for (int j = 0; j < m; j++)
		{
			int f1, f2;
			scanf("%d%d", &f1, &f2);
			relations[f1][f2] = 1;
			relations[f2][f1] = 1;
		}

		// 계산
		int result = get_group_count(relations, visited, 0, 0, n);

		// 출력
		printf("%d\n", result);
	}

	return 0;
}