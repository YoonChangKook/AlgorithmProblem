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
		: capacity(capacity + 1), start(0), end(0)
	{
		arr = new T[this->capacity];
	}

	~queue()
	{
		delete[] arr;
	}

	void push(const T& item)
	{
		end = (end + 1) % capacity;
		arr[end] = item;
	}

	T pop()
	{
		start = (start + 1) % capacity;
		return arr[start];
	}

	const T& front() const
	{
		return arr[(start + 1) % capacity];
	}

	const T& operator[](int index) const
	{
		return arr[(start + 1 + index) % capacity];
	}

	int size() const
	{
		if (start <= end)
			return end - start;
		else
			return capacity + (end - start);
	}

	bool empty() const
	{
		return end == start;
	}

	bool full() const
	{
		return (end + 1) % capacity == start;
	}
};

int n, k;
vector<int> program_codes[MAX_PROGRAM_COUNT];
int pi_ascd[MAX_PROGRAM_LENGTH];
int pi_dscd[MAX_PROGRAM_LENGTH];

// �־��� ���Ͽ� ���� pi���
void calc_pi(const queue<int>& pattern)
{
	int ascd = 0, dscd = 0;
	for (int i = 1; i < pattern.size(); i++)
	{
		// ��������
		while (ascd > 0 && pattern[i] != pattern[ascd])
			ascd = pi_ascd[ascd - 1];

		if (pattern[i] == pattern[ascd])
			pi_ascd[i] = ++ascd;

		// ��������
		while (dscd > 0 && pattern[pattern.size() - 1 - i] != pattern[pattern.size() - 1 - dscd])
			dscd = pi_dscd[dscd - 1];

		if (pattern[pattern.size() - 1 - i] == pattern[pattern.size() - 1 - dscd])
			pi_dscd[i] = ++dscd;
	}
}

// �ڵ� �迭�ȿ� ������ �����ϴ��� kmp�� �˻�
bool calc_kmp(const vector<int>& target_codes, const queue<int>& pattern)
{
	int ascd = 0, dscd = 0;
	for (int i = 0; i < target_codes.size(); i++)
	{
		// ��������
		while (ascd > 0 && target_codes[i] != pattern[ascd])
			ascd = pi_ascd[ascd - 1];

		if (target_codes[i] == pattern[ascd])
		{
			if (ascd == pattern.size() - 1)
				return true;
			else
				ascd++;
		}

		// ��������
		while (dscd > 0 && target_codes[i] != pattern[pattern.size() - 1 - dscd])
			dscd = pi_ascd[dscd - 1];

		if (target_codes[i] == pattern[pattern.size() - 1 - dscd])
		{
			if (dscd == pattern.size() - 1)
				return true;
			else
				dscd++;
		}
	}

	return false;
}

// ��� �ڵ� �迭�� ���� kmp ���
bool calc_virus()
{
	queue<int> pattern(k);
	for (int i = 0; i < k - 1; i++)
		pattern.push(program_codes[0][i]);

	for (int i = k - 1; i < program_codes[0].size(); i++)
	{
		int result = true;

		if (pattern.full())
			pattern.pop();
		pattern.push(program_codes[0][i]);

		// ���� ����
		calc_pi(pattern);

		// ��� �ٸ� ���ڿ��� ���� kmp ����
		for (int j = 1; j < n; j++)
		{
			result = calc_kmp(program_codes[j], pattern);
			if (!result)
				break;
		}

		// ��� �ٸ� ���ڿ��� ���� ��ġ�ϴ� ���ڿ��� ã���� ����
		if (result)
			return true;
	}

	return false;
}

int main()
{
	// �Է�
	scanf("%d%d", &n, &k);
	for (int i = 0; i < n; i++)
	{
		int len, code;
		scanf("%d", &len);
		for (int j = 0; j < len; j++)
		{
			scanf("%d", &code);

			// �ڵ� �Է�
			program_codes[i].push_back(code);
		}
	}

	// ��� �� ���
	printf("%s\n", calc_virus() ? "YES" : "NO");

	return 0;
}