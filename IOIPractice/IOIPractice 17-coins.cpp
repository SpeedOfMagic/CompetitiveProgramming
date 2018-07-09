#include "coins.h"
#include <bits/stdc++.h>
using namespace std;
/*
Suppose there is function f, that takes chessboard and returns some value.
Then, find_coin should return f(b), and
coin_flips should make such chessboard b', that f(b') = c and hemming distance(b, b') = 1.
 
After thinking a few times, I came up with idea that xor value seems best,
since it doesn't care if position is flipped or not, => it can easily change value to the one I want.

So, f(b) = sum((b[i] * i) for i in [0 : 63]).
*/

vector<int> coin_flips(vector<int> b, int c) {
    int cur = 0;
    for (int i = 1; i < 64; i++)
        cur ^= (b[i] * i);

    vector<int> flips;

	for (int i = 0; i < 64; i++)
        if (cur ^ i == c) {
			flips.push_back(i);
			return flips;
		}
	
	assert(0);

}

int find_coin(vector<int> b) {
    int s = 0;
	for (int i = 0; i < 64; i++)
		s ^= (b[i] * i);
	
	return s;
}