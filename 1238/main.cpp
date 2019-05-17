#include <stdio.h>

template <class T>
class vector
{
private:
	int capacity;
	int count;
	T* arr;

public:
	vector()
		: capacity(100), count(0)
	{
		arr = new T[capacity];
	}

	~vector()
	{
		delete[] arr;
	}

	void push_back(const T& obj)
	{
		if (capacity <= count - 1)
			reallocate(capacity * 2);
		arr[count++] = obj;
	}

	void insert(const T& obj, int index)
	{
		if (capacity <= count - 1)
			reallocate(capacity * 2);

		for (int i = count; i > index; i--)
			arr[i] = arr[i - 1];
		arr[index] = obj;
	}

	void remove(int index)
	{
		for (int i = index; i < count - 1; i++)
			arr[i] = arr[i + 1];
	}

	T pop_back()
	{
		return arr[--count];
	}

	T& operator[] (int index)
	{
		return arr[index];
	}

	int get_count()
	{
		return count;
	}

private:
	void reallocate(int new_capacity)
	{
		capacity = new_capacity;

		T* temp_arr = arr;
		arr = new T[new_capacity];
		for (int i = 0; i < count; i++)
			arr[i] = temp_arr[i];
		delete[] temp_arr;
	}
};

template <class T>
class priority_queue
{
private:
	vector<T> nodes;

public:
	void push(const T& node)
	{
		nodes.push_back(node);
		quicksort(nodes, 0, nodes.get_count() - 1);
	}

	T top()
	{
		return nodes[nodes.get_count() - 1];
	}

	T pop()
	{
		return nodes.pop_back();
	}

private:
	void quicksort(vector<T>& arr, int start, int end)
	{
		int pivot = start;
		int left = start, right = end;

		while (left < right)
		{
			// top, pop �Լ��� �� ���� �ε������� �̱⶧���� ���� ����
			while (left < right && arr[right] < arr[pivot]) right--;
			while (left < right && arr[pivot] < arr[left]) left++;
			swap(arr[left], arr[right]);
		}
		swap(arr[pivot], arr[left]);

		if (start < left)
			quicksort(arr, start, left - 1);
		if (right < end)
			quicksort(arr, left + 1, end);
	}

	void swap(T& t1, T& t2)
	{
		T temp = t1;
		t1 = t2;
		t2 = temp;
	}
};

// �������� ���� ����ġ�� ���� ����ü
typedef struct Vertex
{
	int node;
	int weight;

	bool operator < (const Vertex& other)
	{
		return weight < other.weight;
	}
} Vertex;

vector<vector<Vertex>> graph;
priority_queue<Vertex> dists;

int main()
{
	// �켱���� ť, ���� �׽�Ʈ
	priority_queue<int> test;
	int arr[] = { 5, 3, 2, 1, 4 };
	int arr_size = sizeof(arr) / sizeof(int);

	for (int i = 0; i < arr_size; i++)
		test.push(arr[i]);

	for (int i = 0; i < arr_size; i++)
		printf("%d ", test.pop());
	printf("\n");

	return 0;
}