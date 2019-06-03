#include <stdio.h>

#define INIT_CAPACITY 100

template<class T>
class vector
{
private:
	T* arr;
	int capacity;
	int count;

public:
	vector()
		: capacity(INIT_CAPACITY), count(0)
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
		for (int i = 0; i < capacity; i++)
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

template<class T>
class heap
{
private:
	vector<T> arr;

public:
	heap()
	{
		// index는 1부터 시작
		arr.push_back(0);
	}

	void push(const T& item)
	{
		arr.push_back(item);

		int index = arr.size() - 1;
		while (index != 1 && arr[index / 2] < item)
		{
			arr[index] = arr[index / 2];
			index /= 2;
		}
		arr[index] = item;
	}

	T pop()
	{
		int parent = 1;
		int child = 2;
		T root = arr[parent];
		T leaf = arr.pop_back();

		while (child < arr.size())
		{
			// 둘 중 더 큰 노드 선택
			if (child < arr.size() - 1 && arr[child] < arr[child + 1])
				child++;

			// 더이상 큰 노드가 없으면 종료
			if (arr[child] <= leaf)
				break;

			arr[parent] = arr[child];
			parent = child;
			child *= 2;
		}

		arr[parent] = leaf;

		return root;
	}

	const T& top() const
	{
		return arr[1];
	}

	void print() const
	{
		for (int i = 1, pow = 2; i < arr.size(); i++)
		{
			if (i == pow)
			{
				pow *= 2;
				printf("\n");
			}

			printf("%d ", arr[i]);
		}
	}
};

int main()
{
	heap<int> test;

	test.push(9);
	test.push(7);
	test.push(6);
	test.push(5);
	test.push(4);
	test.push(3);
	test.push(2);
	test.push(2);
	test.push(1);
	test.push(3);

	test.print();

	printf("\n\n");

	test.push(8);
	test.print();

	printf("\n\n");

	test.pop();
	test.print();

	return 0;
}