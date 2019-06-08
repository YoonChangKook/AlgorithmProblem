#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

void quicksort(vector<int>& arr, int start, int end)
{
	int pivot = start;
	int left = start, right = end;

	while (left < right)
	{
		while (arr[pivot] < arr[right] && left < right) right--;
		while (arr[left] < arr[pivot] && left < right) left++;
		swap(arr[left], arr[right]);
	}
	swap(arr[left], arr[pivot]);

	if (start < left)
		quicksort(arr, start, left - 1);
	if (left < end)
		quicksort(arr, left + 1, end);
}

int solution(vector<int> budgets, int M) {
	quicksort(budgets, 0, budgets.size() - 1);
	vector<int> budget_sum(budgets);
	for (int i = 1; i < budgets.size(); i++)
		budget_sum[i] += budget_sum[i - 1];

	if (budget_sum[budgets.size() - 1] <= M)
		return budgets[budgets.size() - 1];
	
	int min_value = 0, max_value = budgets[budgets.size() - 1];
	while (min_value != max_value - 1)
	{
		int target_value = (min_value + max_value) / 2;

		int min_index = 0, max_index = budgets.size() - 1;
		while (min_index != max_index - 1)
		{
			int target_index = (min_index + max_index) / 2;
			if (budgets[target_index] < target_value)
				min_index = target_index;
			else
				max_index = target_index;
		}

		if ((target_value < budget_sum[0] && target_value * budgets.size() <= M) ||
			(budget_sum[min_index] + target_value * (budgets.size() - 1 - min_index) <= M))
			min_value = target_value;
		else
			max_value = target_value;
	}

	return min_value;
}

int main()
{
	int result = solution({ 150, 110, 140, 120 }, 443);
	printf("%d\n", result);

	result = solution({ 100, 110, 140, 120 }, 7);
	printf("%d\n", result);

	return 0;
}