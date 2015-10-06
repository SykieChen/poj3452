#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

void solve(int ctcars, int cttracks, int cars[]) {
	int inorder[2000], outorder[2000], trackidx = 0, tracklast[2000] = { 0 };

	for (int i = 0; i < ctcars; i++) {
		inorder[i] = -1;
		for (int j = 0; j < trackidx; j++) {
			if (tracklast[j] == cars[i] - 1) {
				inorder[i] = j;
				tracklast[j]++;
				outorder[cars[i]] = j;
			}
		}
		if (inorder[i] == -1) {
			if (trackidx < cttracks) {
				inorder[i] = trackidx;
				tracklast[trackidx] = cars[i];
				outorder[cars[i]] = trackidx;
				trackidx++;
			}
			else {
				cout << "Transportation failed\n";
				return;
			}
		}
	}
	for (int i = 0; i < ctcars; i++) cout << inorder[i] << ' ';
	cout << '\n';
	for (int i = 0; i < ctcars; i++) cout << outorder[i] << ' ';
	cout << '\n';
	return;
}

int main() {
	int data[2000] = { 4,2,5,3,1 };
	solve(5, 3, data);
	return 0;
}