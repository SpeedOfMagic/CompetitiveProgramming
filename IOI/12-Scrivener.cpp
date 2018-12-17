/* Solution: persistent segment tree that has low memory.
TypeLetter - update element at the end position (which should be counted separately).
UndoCommands - add version that looks like the last uncancelled one.
GetLetter - getting element at position.
*/
#include "grader.h"
#include <bits/stdc++.h>
using namespace std;

const int N = 1048576; //2^20
const int M = 20;

int version[N][M];
//version[i][j] < 0 means that j-th node of i-th version has left child is version[|version[i][j]|][j + 1]
//and right child is version[i][j + 1]. version[i][j] > 0 means right child is version[|version[i][j]|][j + 1]
char val[N];
int ptr = 0;
int siz[N];

void Init() {
	siz[0] = 0;
	for (int i = 0; i < M; i++)
		version[0][i] = 0;
}

void TypeLetter(char L) {
	int parallel = ptr;
	ptr++;
	siz[ptr] = siz[ptr - 1] + 1;
	int p = siz[ptr];
	val[ptr] = L;
	
	int l = 1, r = N;
	for(int i = 0; i < M; i++) {
		int mid = (l + r) >> 1;
		if (p > mid) {
			l = mid + 1;
			if (version[parallel][i] < 0)
				version[ptr][i] = version[parallel][i];
			else
			    version[ptr][i] = -parallel;
			if (version[parallel][i] > 0)
				parallel = version[parallel][i];
		} else {
			r = mid;
			if (version[parallel][i] > 0)
				version[ptr][i] = version[parallel][i];
			else
				version[ptr][i] = parallel;
			if (version[parallel][i] < 0)
				parallel = version[parallel][i];
		}	
	}
}

void UndoCommands(int U) {
	int from = ptr - U;
	ptr++;
	siz[ptr] = siz[from];
	val[ptr] = val[from];
	for (int i = 0; i < M; i++)
		version[ptr][i] = version[from][i];
}

char GetLetter(int P) {
	P++;
	int l = 1, r = N;
	int cur = ptr;
	
	for (int i = 0; i < M; i++) {
		int mid = (l + r) >> 1;
		if (P > mid) {
			l = mid + 1;
			if (version[cur][i] > 0)
				cur = version[cur][i];
		} else {
			r = mid;
			if (version[cur][i] < 0)
				cur = -version[cur][i];
		}
	}
	
	return val[cur];
}
