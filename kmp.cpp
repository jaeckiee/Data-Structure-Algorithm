#include <iostream>
#include <string>
#include <vector>

using namespace std;
int* pre_suffix_array(string pattern) {
	int len = pattern.length();
	int* arr = new int[len + 1];
	bool suc;
	arr[0] = -1;
	arr[1] = 0;
	if (len > 1) {
		for (int i = 2; i < len + 1; i++) {
			suc = false;
			if (arr[i - 1] == 0) {
				if (pattern[i - 1] == pattern[0]) {
					arr[i] = 1;
				}
				else {
					arr[i] = 0;
				}
			}
			else {
				if (pattern[i - 1] == pattern[arr[i - 1]]) {
					arr[i] = arr[i - 1] + 1;
				}
				else {
					for (int j = arr[i - 1]; j >= 0; j--) {
						if (suc) {
							break;
						}
						else {
							if (j == 0) {
								arr[i] = 0;
								suc = true;
							}
							else {
								for (int k = 0; k < j; k++) {
									if (pattern[k] != pattern[i - j + k]) {
										break;
									}
									if (k == j - 1) {
										arr[i] = j;
										suc = true;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return arr;
}

void kmp(string text, string pattern) {
	vector<int> v;
	int* arr;
	int index;
	int txtlen;
	int patlen;
	int size;
	int index2;
	index = 0;
	index2 = 0;
	txtlen = text.length();
	patlen = pattern.length();
	arr = pre_suffix_array(pattern);
	while (index <= txtlen - patlen) {
		for (int i = index2; i < patlen; i++) {
			if (text[index + i] != pattern[i]) {
				index = index + (i - arr[i]);
				if (arr[i] == -1) {
					index2 = 0;
				}
				else {
					index2 = arr[i];
				}
				break;
			}
			if (i == patlen - 1) {
				v.push_back(index + i - (patlen - 1) + 1);
				index = index + (i + 1 - arr[i + 1]);
				index2 = arr[i + 1];
			}
		}
	}
	size = v.size();
	printf("%d\n", size);
	if (size > 0) {
		for (int i = 0; i < size; i++) {
			printf("%d ", v[i]);
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	string text;
	string pattern;
	getline(cin, text, '\n');
	getline(cin, pattern, '\n');
	kmp(text, pattern);
	return 0;
}