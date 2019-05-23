#include <string>
#include <vector>
#include <map>
#include <algorithm>

#define MAX_PHONE_NUMBER_LENGTH 20

using namespace std;

bool compare_by_size(const string& str1, const string& str2)
{
	return str1.size() < str2.size();
}

bool solution(vector<string> phone_book) {
	bool answer = true;

	map<string, int> phone_number_by_len[MAX_PHONE_NUMBER_LENGTH + 1];
	sort(phone_book.begin(), phone_book.end(), compare_by_size);

	for (int i = 0; i < phone_book.size(); i++)
	{
		const string& target_str = phone_book[i];

		// 이전 문자열들 검사
		char target_char_array[MAX_PHONE_NUMBER_LENGTH + 1];
		strcpy(target_char_array, target_str.c_str());
		for (int j = target_str.size() - 1; j > 0; j--)
		{
			target_char_array[j] = '\0';
			if (phone_number_by_len[j].find(target_char_array) != phone_number_by_len[j].end())
				return false;
		}

		phone_number_by_len[target_str.size()][target_str] = 1;
	}

	return answer;
}

int main()
{
	//vector<string> param = { "119", "97674223", "1195524421" };
	vector<string> param = { "123", "456", "789" };

	printf("%s\n", solution(param) ? "true" : "false");

	return 0;
}