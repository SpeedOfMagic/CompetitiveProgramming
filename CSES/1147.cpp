/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
For every i from 0 to n - 1, let's keep array curSeg of m elements,
where curSeg[j] is the maximum length of vertical segment that ends on element in i-th row, j-th column.

Suppose that rectangle of maximum area ends on row #i, for every i from 0 to n - 1.
Then, I look at curSeg #i,
and I need to find such contigous subarray that (minimum of this subarray) * (length of segment) is maximized.

For that I can find for each element in curSeg #j such index #k, that:
	1. k < j
	2. curSeg[k] < curSeg[j]
	3. k is maximized
	
It can be done by ... algorithm. After that, I want to do the same, but instead of '1. k < j', there will be '1. k > j'
Then, for every j in [0; m - 1], I assume that curSeg[j] will be minimum of subarray.
Then, I need to find its maximum length. And this maximum length will be: indexLowerRight[j] - indexLowerLeft[j] + 1;
Then, I take maximum of those areas, and answer is maximum of them.

Time complexity: O(nm).
*/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin>>
#define put fout<<
#else
#define get cin>>
#define put cout<<
#endif
#define eol put endl
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
void run() {
    int n, m;
    read(n, m);
    int curSeg[m];
    rep(i, 0, m)
        curSeg[i] = 0;

    int ans = 0;

    rep(i, 0, n) {
        str cur;
        get cur;
        rep(j, 0, m)
            if (cur[j] == '.')
                curSeg[j]++;
            else
                curSeg[j] = 0;

        stack<int> index;
        int indexLowerLeft[m];
        rep(j, 0, m) {
            while (!index.empty() && curSeg[index.top()] >= curSeg[j])
                index.pop();

            if (!index.empty())
                indexLowerLeft[j] = index.top();
            else
                indexLowerLeft[j] = -1;

            index.push(j);
        }

        int indexLowerRight[m];
        index = stack<int>();

        for (int j = m - 1; j >= 0; j--) {
            while (!index.empty() && curSeg[index.top()] >= curSeg[j])
                index.pop();

            if (!index.empty())
                indexLowerRight[j] = index.top();
            else
                indexLowerRight[j] = m;

            index.push(j);
        }

        rep(j, 0, m) {
            int l = indexLowerLeft[j] + 1;
            int r = indexLowerRight[j] - 1;
            //debug(i, j, l, r, curSeg[j]);
            ans = max(ans, (r - l + 1) * curSeg[j]);
        }
    }

    put ans;
}
/**
1 1
**/
int32_t main() {srand(time(0));cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
