#include <stdio.h>

#define INF 0x7fffffff
#define MAX_NODE_COUNT 20000

template <class T>
class vector
{
private:
	T* arr;
	int capacity;
	int count;

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

	vector(int count)
		: capacity(count), count(count)
	{
		arr = new T[count];
	}

	vector(int count, T init_value)
		: capacity(count), count(count)
	{
		arr = new T[count];
		for (int i = 0; i < count; i++)
			arr[i] = init_value;
	}

	vector(const vector<T>& other)
	{
		delete[] arr;
		arr = new T[other.capacity];
		for (int i = 0; i < other.count; i++)
			arr[i] = other.arr[i];
		capacity = other.capacity;
		count = other.count;
	}

	void push_back(const T & item)
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
		T* new_arr = new T[new_capacity];
		for (int i = 0; i < count; i++)
			new_arr[i] = arr[i];
		delete[] arr;
		
		arr = new_arr;
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
		if (left < end)
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
	int node;
	int weight;

	bool operator <= (const Vertex& other) const
	{
		return weight <= other.weight;
	}
} Vertex;

int n, m;
vector<vector<Vertex>> graph(MAX_NODE_COUNT);
int max_dist;

// 최장거리의 노드들을 반환한다.
vector<int> find_farthest_dist_nodes()
{
	max_dist = 0;
	vector<int> dists(MAX_NODE_COUNT, INF);
	priority_queue<Vertex> queue;
	dists[0] = 0;
	queue.push({ 0, 0 });

	// 거리 계산
	while (!queue.empty())
	{
		Vertex top = queue.top();
		queue.pop();

		if (top.weight != dists[top.node])
			continue;

		const vector<Vertex>& target = graph[top.node];
		for (int i = 0; i < target.size(); i++)
		{
			if (target[i].weight + top.weight < dists[target[i].node])
			{
				dists[target[i].node] = target[i].weight + top.weight;
				queue.push({ target[i].node, dists[target[i].node] });
				if (max_dist < dists[target[i].node])
					max_dist = dists[target[i].node];
			}
		}
	}

	// 거리 중 최장거리를 가진 노드들 선출
	vector<int> result;
	for (int i = 0; i < n; i++)
		if (dists[i] == max_dist)
			result.push_back(i);

	return result;
}

int main()
{
	// 입력
	scanf("%d%d", &n, &m);
	int from, to;
	for (int i = 0; i < m; i++)
	{
		scanf("%d%d", &from, &to);
		graph[from - 1].push_back({ to - 1, 1 });
		graph[to - 1].push_back({ from - 1, 1 });
	}

	// 계산
	vector<int> result = find_farthest_dist_nodes();

	// 출력
	printf("%d %d %d\n", result[0] + 1, max_dist, result.size());

	return 0;
}