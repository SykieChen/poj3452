#define _CRT_SECURE_NO_WARNINGS
#include <iostream>

using namespace std;

/*后进的车厢与铁轨中已有的车厢编号之间不能间隔
即不能有其他车厢的编号介于两者之间
出铁轨时按车厢号大小检索排序*/

int cars[200000];
//自建比较函数用于 qsort，以车厢号作为判断依据（懒得建结构体，用全局数组代替）
int compare(const void *a, const void *b) {
	return cars[*(int*)a] - cars[*(int*)b];
}

void solve(int ctcars, int cttracks) {
	//数组太大，必须动态分配
	int *inorder = new int[200000];
	int *outorder = new int[200000];
	int *tracklast = new int[200000];
	int trackidx = 0, minsp;

	tracklast[0] = 0;

	//遍历所有车厢
	for (int i = 0; i < ctcars; i++) {
		//初始化
		inorder[i] = -1;
		outorder[i] = i;
		minsp = 1<<30;
		//扫描所有轨道里的最后车厢确定最小车厢号间隔值（防止重号和间断）
		for (int j = 0; j <= trackidx; j++) {
			if ((cars[i] - tracklast[j] < minsp)&&(cars[i] - tracklast[j] >= 0)){
				minsp = cars[i] - tracklast[j];
			}
		}
		//cout << minsp << '\n';
		//扫描轨道最后车厢决定当前车厢要进入的轨道
		for (int j = 0; j < trackidx; j++) {
			if (tracklast[j] == cars[i] - minsp){
				inorder[i] = j;//保存i号车厢的轨道号j
				tracklast[j] = cars[i];//轨道内最后车厢更新
			}
		}
		if (inorder[i] == -1) {//若未找到可用轨道，则开辟新轨道
			if (trackidx < cttracks) {
				inorder[i] = trackidx;
				tracklast[trackidx] = cars[i];
				trackidx++;
				tracklast[trackidx] = 0;
			}
			else {//若轨道数不足，返回错误
				printf("Transportation failed\n");
				delete[] inorder;
				delete[] outorder;
				delete[] tracklast;
				return;
			}
		}
	}
	//输出进轨道顺序
	for (int i = 0; i < ctcars; i++) {
		printf("%d",inorder[i] + 1);
		if (i < ctcars - 1) printf(" ");
	}
	if (ctcars > 0) printf("\n");
	//以车厢号为序排序对应的轨道号
	qsort(outorder, ctcars, sizeof(int), compare);
	//输出轨道号
	for (int i = 0; i < ctcars; i++) {
		printf("%d", inorder[outorder[i]] + 1);
		if (i < ctcars - 1) printf(" ");
	}
	/*旧版排序-超时
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
	//资源回收
	delete[] inorder;
	delete[] outorder;
	delete[] tracklast;
	return;
}

int main() {
	/*
	//缓存输入内容后统一输出--不必，一组一组输出即可
	int size = 200;
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