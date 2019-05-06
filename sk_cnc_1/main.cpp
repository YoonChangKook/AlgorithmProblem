#include <stdio.h>

typedef struct DriveInfo {
	int dist_;
	int hour_;
} DriveInfo;

void swapDriveInfo(DriveInfo& di1, DriveInfo& di2)
{
	DriveInfo temp = di1;
	di1 = di2;
	di2 = temp;
}

void quicksortByHour(DriveInfo drive_infos[], int start, int end)
{
	int pivot_hour = drive_infos[start].hour_;
	int left = start, right = end;

	while (left < right)
	{
		while (pivot_hour <= drive_infos[right].hour_ && left < right) right--;
		while (pivot_hour >= drive_infos[left].hour_ && left < right) left++;
		if (left < right)
			swapDriveInfo(drive_infos[left], drive_infos[right]);
	}

	swapDriveInfo(drive_infos[start], drive_infos[left]);

	if (start < left)
		quicksortByHour(drive_infos, start, left - 1);
	if (right < end)
		quicksortByHour(drive_infos, left + 1, end);
}

int main()
{
	int speed_limit = 50;
	DriveInfo drive_infos[] = { {240, 4}, {100, 1}, {500, 6} };
	int drive_info_count = sizeof(drive_infos) / sizeof(DriveInfo);
	int exceed_count = 0;

	// 시간순으로 정렬
	quicksortByHour(drive_infos, 0, drive_info_count - 1);

	// 계산
	if (speed_limit < drive_infos[0].dist_ / drive_infos[0].hour_) // 시작지점 계산
		exceed_count++;
	for (int i = 0; i < drive_info_count - 1; i++)
	{
		const DriveInfo& start = drive_infos[i];
		const DriveInfo& end = drive_infos[i + 1];

		if (speed_limit < (end.dist_ - start.dist_) / (end.hour_ - start.hour_))
			exceed_count++;
	}

	// 출력
	printf("%d\n", exceed_count);

	return 0;
}