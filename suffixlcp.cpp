#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

//void merge(int** arr, int left, int mid, int right, int casenum) {
//	int l, m, l2, m2, l3, m3;
//	int a, b;
//	int index;
//	int index2;
//	int index3;
//	int* sorted;
//	int* sorted2;
//	int* sorted3;
//	l = left;
//	l2 = left;
//	l3 = left;
//	m = mid + 1;
//	m2 = mid + 1;
//	m3 = mid + 1;
//	index = 0;
//	index2 = 0;
//	index3 = 0;
//	sorted = new int[right - left + 1];
//	sorted2 = new int[right - left + 1];
//	sorted3 = new int[right - left + 1];
//	if (casenum == 0) {
//		a = 0;
//		b = 1;
//	}
//	else {
//		a = 1;
//		b = 0;
//	}
//	while (l <= mid && m <= right) {
//		if (arr[l][a] <= arr[m][a]) {
//			sorted[index++] = arr[l++][a];
//			sorted2[index2++] = arr[l2++][b];
//			sorted3[index3++] = arr[l3++][2];
//		}
//		else {
//			sorted[index++] = arr[m++][a];
//			sorted2[index2++] = arr[m2++][b];
//			sorted3[index3++] = arr[m3++][2];
//		}
//	}
//	while (l <= mid) {
//		sorted[index++] = arr[l++][a];
//		sorted2[index2++] = arr[l2++][b];
//		sorted3[index3++] = arr[l3++][2];
//	}
//	while (m <= right) {
//		sorted[index++] = arr[m++][a];
//		sorted2[index2++] = arr[m2++][b];
//		sorted3[index3++] = arr[m3++][2];
//	}
//	for (int i = 0; i < (right - left + 1); i++) {
//		arr[left + i][a] = sorted[i];
//		arr[left + i][b] = sorted2[i];
//		arr[left + i][2] = sorted3[i];
//	}
//	delete[] sorted;
//	delete[] sorted2;
//	delete[] sorted3;
//}
//void mergesort(int** arr, int left, int right, int casenum) {
//	int mid;
//	if (left < right) {
//		mid = (left + right) / 2;
//		mergesort(arr, left, mid, casenum);
//		mergesort(arr, mid + 1, right, casenum);
//		merge(arr, left, mid, right, casenum);
//	}
//}

void countingsort(int** arr, int len, int casenum) {
	int* countingarr;
	int** resarr;
	int count;
	int index;
	int a, b;
	countingarr = new int[500001];
	resarr = new int*[len];
	for (int i = 0; i < len; i++) {
		resarr[i] = new int[3];
	}
	if (casenum == 0) {
		a = 0;
		b = 1;
	}
	else {
		b = 0;
		a = 1;
	}
	for (int i = 0; i < 500001; i++) {
		countingarr[i] = 0;
	}
	for (int i = 0; i < len; i++) {
		countingarr[arr[i][a]] = countingarr[arr[i][a]] + 1;
	}
	count = 0;
	for (int i = 0; i < 500001; i++) {
		if (countingarr[i] != 0) {
			count = count + countingarr[i];
			countingarr[i] = count;
		}
	}
	for (int i = len - 1; i >= 0; i--) {
		index = countingarr[arr[i][a]] - 1;
		countingarr[arr[i][a]] = countingarr[arr[i][a]] - 1;
		resarr[index][a] = arr[i][a];
		resarr[index][b] = arr[i][b];
		resarr[index][2] = arr[i][2];
	}
	for (int i = 0; i < len; i++) {
		arr[i][0] = resarr[i][0];
		arr[i][1] = resarr[i][1];
		arr[i][2] = resarr[i][2];
	}
	delete[] countingarr;
	for (int i = 0; i < len; i++) {
		delete[] resarr[i];
	}
	delete[] resarr;
}

void sorting(int* suffixarr, int len, int gap) {
	if (gap < len) {
		int** sortedarr;
		int count = 0;
		int tmp1, tmp2;
		sortedarr = new int*[len];
		for (int i = 0; i < len; i++) {
			sortedarr[i] = new int[3];
		}
		for (int i = 0; i < len; i++) {
			sortedarr[i][0] = suffixarr[i];
			if ((i + gap) < len) {
				sortedarr[i][1] = suffixarr[i + gap];
			}
			else {
				sortedarr[i][1] = 0;
			}
			sortedarr[i][2] = i;
		}
		countingsort(sortedarr, len, 1);
		countingsort(sortedarr, len, 0);
	/*	mergesort(sortedarr, 0, len - 1, 1);
		mergesort(sortedarr, 0, len - 1, 0);*/
		tmp1 = -1;
		tmp2 = -1;
		for (int i = 0; i < len; i++) {
			if (tmp1 != sortedarr[i][0] || tmp2 != sortedarr[i][1]) {
				count++;
				suffixarr[sortedarr[i][2]] = count;
				tmp1 = sortedarr[i][0];
				tmp2 = sortedarr[i][1];
			}
			else {
				suffixarr[sortedarr[i][2]] = count;
			}
		}
		for (int i = 0; i < len; i++) {
			delete[] sortedarr[i];
		}
		delete[] sortedarr;
		if (count == len) {
			return;
		}
		sorting(suffixarr, len, gap * 2);
	}
}

int* getSuffixArray(string str) {
	int count;
	int* suffixarr;
	int* resultarr;
	bool* bcountingsort;
	int* countingsort;
	int len;
	count = 0;
	len = str.length();
	suffixarr = new int[len];
	resultarr = new int[len];
	bcountingsort = new bool[26];
	countingsort = new int[26];
	for (int i = 0; i < 26; i++) {
		bcountingsort[i] = false;
	}
	for (int i = 0; i < len; i++) {
		bcountingsort[str[i] - 'a'] = true;
	}
	for (int i = 0; i < 26; i++) {
		if (bcountingsort[i] == true) {
			count++;
			countingsort[i] = count;
		}
		else {
			countingsort[i] = -1;
		}
	}
	for (int i = 0; i < len; i++) {
		suffixarr[i] = countingsort[str[i] - 'a'];
	}
	delete[] countingsort;
	delete[] bcountingsort;
	sorting(suffixarr, len, 1);
	for (int i = 0; i < len; i++) {
		resultarr[suffixarr[i] - 1] = i + 1;
	}
	delete[] suffixarr;
	return resultarr;
}

int* getLCP(string str, int* suffixarr) {
	int* lcp;
	int* rank;
	int len;
	int minlen;
	int count;
	len = str.length();
	lcp = new int[len];
	rank = new int[len];
	for (int i = 0; i < len; i++) {
		rank[suffixarr[i] - 1] = i;
	}
	count = 0;
	for (int i = 0; i < len; i++) {
		if (rank[i] == 0) {
			lcp[rank[i]] = 0;
		}
		else {
			minlen = min(len - suffixarr[rank[i]] + 1, len - suffixarr[rank[i] - 1] + 1);
			for (int j = count; j < minlen; j++) {
				if (str[suffixarr[rank[i]] - 1 + j] == str[suffixarr[rank[i] - 1] - 1 + j]) {
					count++;
				}
				else {
					break;
				}
			}
			lcp[rank[i]] = count;
			count = max(count - 1, 0);
		}
	}
	return lcp;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	int* suffixarr;
	int* lcp;
	int len;
	string str;
	cin >> str;
	len = str.length();
	suffixarr = getSuffixArray(str);

	for (int i = 0; i < len; i++) {
		printf("%d ", suffixarr[i]);
	}
	printf("\n");
	lcp = getLCP(str, suffixarr);
	printf("x ");
	if (len > 1) {
		for (int i = 1; i < len; i++) {
			printf("%d ", lcp[i]);
		}
	}
	printf("\n");
	return 0;
}