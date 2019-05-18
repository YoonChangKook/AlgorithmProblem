#include <stdio.h>

#define INF 0x7fffffff

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

	vector(const vector<T>& other)
	{
		capacity = other.capacity;
		count = other.count;
		arr = new T[capacity];
		for (int i = 0; i < count; i++)
			arr[i] = other.arr[i];
	}

	void push_back(const T& obj)
	{
		if (capacity <= count)
			reallocate(capacity * 2);
		arr[count++] = obj;
	}

	void insert(const T& obj, int index)
	{
		if (capacity - 1 <= count)
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

	T operator[] (int index) const
	{
		return arr[index];
	}

	T& operator[] (int index)
	{
		return arr[index];
	}

	int get_count() const
	{
		return count;
	}

	void set_count(int count)
	{
		if (capacity < count)
		{
			int new_capacity = capacity;
			while (new_capacity < count)
				new_capacity *= 2;
			reallocate(new_capacity);
		}

		this->count = count;
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

	T top() const
	{
		return nodes[nodes.get_count() - 1];
	}

	T pop()
	{
		return nodes.pop_back();
	}

	int get_count() const
	{
		return nodes.get_count();
	}

	bool is_empty() const
	{
		return nodes.get_count() == 0;
	}

private:
	void quicksort(vector<T>& arr, int start, int end)
	{
		int pivot = start;
		int left = start, right = end;

		while (left < right)
		{
			// top, pop �Լ��� �� ���� �ε������� �̱⶧���� ���� ����
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

	// ����ġ �� ����
	bool operator <= (const Vertex& other)
	{
		return weight <= other.weight;
	}
} Vertex;

int n, m, x;
vector<vector<Vertex>> graph;

// start_node�κ��� �ٸ� ��� ��������� ����ġ ��ȯ
vector<int> dijkstra(int start_node)
{
	vector<int> result;
	for (int i = 0; i < graph.get_count(); i++)
		result.push_back(INF);
	result[start_node] = 0;
	priority_queue<Vertex> dist_queue;
	dist_queue.push({ start_node, 0 });

	while (!dist_queue.is_empty())
	{
		Vertex top = dist_queue.pop();
		
		const vector<Vertex>& target_graph = graph[top.node];
		for (int i = 0; i < target_graph.get_count(); i++)
		{
			if (top.weight != result[top.node])
				continue;

			if (target_graph[i].weight + top.weight < result[target_graph[i].node])
			{
				result[target_graph[i].node] = target_graph[i].weight + top.weight;
				dist_queue.push({ target_graph[i].node, result[target_graph[i].node] });
			}
		}
	}

	return result;
}

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

	// �Է�
	scanf("%d%d%d", &n, &m, &x);
	graph.set_count(n);
	for (int i = 0; i < m; i++)
	{
		int from, to, time;
		scanf("%d%d%d", &from, &to, &time);
		graph[from - 1].push_back({ to - 1, time });
	}

	// ���
	vector<int> result = dijkstra(x - 1);
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == x - 1)
			continue;

		result[i] += dijkstra(i)[x - 1];
		if (max < result[i])
			max = result[i];
	}

	// ���
	printf("%d\n", max);

	return 0;
}