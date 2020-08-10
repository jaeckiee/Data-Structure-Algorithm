#include <iostream>

using namespace std;

void bubblesort(int arr[], int len) {
	int tmp;
	if (len <= 1) {
		return;
	}
	else {
		for (int i = 0; i < len - 1; i++) {
			for (int j = 0; j < len - 1 - i; j++) {
				if (arr[j] > arr[j + 1]) {
					tmp = arr[j];
					arr[j] = arr[j + 1];
					arr[j + 1] = tmp;
				}
			}
		}
	}

	
}

int main() {
	int arr[] = { 10, 2, 3, 6, 8, 7, 9 };
	int len = sizeof(arr) / sizeof(arr[0]);
	bubblesort(arr, len);
	for (int i = 0; i < len; i++) {
		cout << arr[i] << ' ';
	}
	return 0;
}