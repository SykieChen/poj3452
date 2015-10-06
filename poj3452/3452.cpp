#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <algorithm>

using namespace std;

int cars[200000];

int compare(const void *a, const void *b) {
	return cars[*(int*)a] - cars[*(int*)b];
}

void solve(int ctcars, int cttracks) {
	int *inorder = new int[200000];
	int *outorder = new int[200000];
	int *tracklast = new int[200000];
	int trackidx = 0, minsp;

	tracklast[0] = 0;


	for (int i = 0; i < ctcars; i++) {
		inorder[i] = -1;
		outorder[i] = i;
		minsp = 1<<30;
		for (int j = 0; j <= trackidx; j++) {
			if ((cars[i] - tracklast[j] < minsp)&&(cars[i] - tracklast[j] >= 0)){
				minsp = cars[i] - tracklast[j];
			}
		}
		//cout << minsp << '\n';
		for (int j = 0; j < trackidx; j++) {
			if (tracklast[j] == cars[i] - minsp){
				inorder[i] = j;
				tracklast[j] = cars[i];
			}
		}
		if (inorder[i] == -1) {
			if (trackidx < cttracks) {
				inorder[i] = trackidx;
				tracklast[trackidx] = cars[i];
				trackidx++;
				tracklast[trackidx] = 0;
			}
			else {
				printf("Transportation failed\n");
				delete[] inorder;
				delete[] outorder;
				delete[] tracklast;
				return;
			}
		}
	}
	for (int i = 0; i < ctcars; i++) {
		printf("%d",inorder[i] + 1);
		if (i < ctcars - 1) printf(" ");
	}
	if (ctcars > 0) printf("\n");
	qsort(outorder, ctcars, sizeof(int), compare);
	for (int i = 0; i < ctcars; i++) {
		printf("%d", inorder[outorder[i]] + 1);
		if (i < ctcars - 1) printf(" ");
	}
	/*
	sort(outorder, outorder + ctcars);
	for (int i = 0; i < ctcars; i++) {
		for (int j = 0; j < ctcars; j++) {
			if (cars[j] == outorder[i]) {
				printf("%d", inorder[j] + 1);
				cars[j] = 0;
				if (i < ctcars - 1) printf(" ");
			}
		}
	}*/
	if (ctcars > 0) printf("\n");
	delete[] inorder;
	delete[] outorder;
	delete[] tracklast;
	return;
}

int main() {
	/*int size = 200;
	int(*cars)[200000] = new int[size][200000];
	int ctcars[200], cttracks[200], i = 0;
	do {
		cin >> ctcars[i] >> cttracks[i];
		for (int j = 0; j < ctcars[i]; j++) cin >> cars[i][j];
	} while (ctcars[i++] != 0);
	i = 0;
	do {
		solve(ctcars[i], cttracks[i], cars[i]);
	} while (ctcars[++i] != 0);
	delete[] cars;*/
	int ctcars, cttracks, i = 0;
	do {
		cin >> ctcars >> cttracks;
		for (int j = 0; j < ctcars; j++) cin >> cars[j];
		solve(ctcars, cttracks);
	} while (ctcars != 0);
	return 0;
}