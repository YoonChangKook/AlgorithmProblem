#include <stdio.h>

#define MAX_PROGRAM_COUNT 100
#define MAX_PROGRAM_LENGTH 1000

template<class T>
class vector
{
private:
	T* arr;
	int capacity;
	int count;

public:
	vector()
		: capacity(MAX_PROGRAM_LENGTH), count(0)
	{
		arr = new T[capacity];
	}

	~vector()
	{
		delete[] arr;
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

	T& operator[](int index)
	{
		return arr[index];
	}

	const T& operator[](int index) const
	{
		return arr[index];
	}

	int size() const
	{
		return count;
	}

private:
	void reallocate(int new_capacity)
	{
		T* new_arr = new T[new_capacity];
		for (int i = 0; i < capacity; i++)
			new_arr[i] = arr[i];
		delete[] arr;

		arr = new_arr;
		capacity = new_capacity;
	}
};

template <class T>
class queue
{
private:
	T* arr;
	int capacity;
	int start;
	int end;

public:
	queue(int capacity)
		: capacity(capacity), start(0), end(0)
	{
		arr = new T[capacity];
	}

	~queue()
	{
		delete[] arr;
	}

	void push(const T& item)
	{
		arr[end] = item;
		end = (end + 1) % capacity;
	}

	T pop()
	{
		return arr[start];
		start = (start + 1) % capacity;
	}

	const T& front() const
	{
		return arr[start];
	}

	int size() const
	{
		if (start <= end)
			return end - start;
		else
			return capacity + (end - start);
	}
};

int n, k;
vector<int> program_codes[MAX_PROGRAM_COUNT];
vector<int> sum_ascd[MAX_PROGRAM_COUNT];
vector<int> sum_desd[MAX_PROGRAM_COUNT];

int main()
{
	// 입력
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		int len, code;
		scanf("%d", &len);
		for (int j = 0; j < len; j++)
		{
			scanf("%d", &code);
			program_codes[i].push_back(code);
		}
	}

	// 계산

	return 0;
}