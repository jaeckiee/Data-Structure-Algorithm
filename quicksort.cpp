#include <iostream>

using namespace std;

void swap(int& num1, int& num2) {
	int tmp;
	tmp = num1;
	num1 = num2;
	num2 = tmp;
}

int calpivot(int dataarray[], int left, int right) {
	int first = left;
	int pivotnumber = dataarray[first];
	left++;
	while (left <= right) {
		while ((dataarray[left] <= pivotnumber) && (left < right)) {
			left++;
		}
		while ((dataarray[right] > pivotnumber) && (left <= right)) {
			right--;
		}
		if (left < right) {
			swap(dataarray[left], dataarray[right]);
		}
		else {
			break;
		}
	}
	swap(dataarray[first], dataarray[right]);
	return right;
}

void quickSort(int dataarray[], int left, int right) {
	if (left < right) {
		int pivot = calpivot(dataarray, left, right);
		quickSort(dataarray, left, pivot - 1);
		quickSort(dataarray, pivot + 1, right);
	}
}

int main() { 
	int arr[] = { 5, 1, 3, 2, 4, 7, 8 };
	quickSort(arr, 0, 6);
	for (int i = 0; i < 7; i++) {
		cout << arr[i] << endl;
	}
	return 0;
}