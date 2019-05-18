#include <stdio.h>

#define INF 0x7fffffff
#define MAX_NODE_COUNT 1000

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
			// top, pop 함수가 맨 뒤의 인덱스부터 뽑기때문에 역순 정렬
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

// 정점까지 가는 가중치를 담은 구조체
typedef struct Vertex
{
	int node;
	int weight;

	// 가중치 순 정렬
	bool operator <= (const Vertex& other)
	{
		return weight <= other.weight;
	}
} Vertex;

int n, m, x;
vector<Vertex> row_major_graph[MAX_NODE_COUNT];
vector<Vertex> column_major_graph[MAX_NODE_COUNT];

// start_node로부터 다른 모든 노드들까지의 가중치 반환
vector<int> dijkstra(int start_node, bool to_party)
{
	vector<int> result;
	for (int i = 0; i < n; i++)
		result.push_back(INF);
	result[start_node] = 0;
	priority_queue<Vertex> dist_queue;
	dist_queue.push({ start_node, 0 });

	while (!dist_queue.is_empty())
	{
		Vertex top = dist_queue.pop();
		const vector<Vertex>& target_graph = to_party ? column_major_graph[top.node] : row_major_graph[top.node];

		if (top.weight != result[top.node])
			continue;

		for (int i = 0; i < target_graph.get_count(); i++)
		{
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
	// 입력
	scanf("%d%d%d", &n, &m, &x);
	for (int i = 0; i < m; i++)
	{
		int from, to, time;
		scanf("%d%d%d", &from, &to, &time);
		row_major_graph[from - 1].push_back({ to - 1, time });
		column_major_graph[to - 1].push_back({ from - 1, time });
	}

	// 계산
	vector<int> to_party = dijkstra(x - 1, true);
	vector<int> from_party = dijkstra(x - 1, false);
	int max = 0;
	for (int i = 0; i < n; i++)
	{
		if (i == x - 1)
			continue;

		if (max < from_party[i] + to_party[i])
			max = from_party[i] + to_party[i];
	}

	// 출력
	printf("%d\n", max);

	return 0;
}