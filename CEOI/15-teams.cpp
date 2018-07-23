/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
0. I want to formalize statement: An array b is constructed by following algorithm:
	b[0] = 1
	for each i in range [1; n - 1],	b[i] may be equal to [1 : max(b[0], b[1], ..., b[i - 1]) + 1].
All possible arrays constructed by that algorithm are lexicographically sorted;
A possible array a is given, find number of its position in lexicographical sorting.
		
1. Suppose current element is a[i]. Then, for each l in [1; a[i] - 1],
	I want to find amount of arrays that start with: {a[0], a[1], ... , l}.
	2. It can be done with dp: suppose dp[i][j] - amount of arrays, who end at element i and have maximum of (j + 1).
	3. Then, dp[i][max(a[0], a[1], ..., a[i - 1]] = a[i] - 1; (every possible l);
	dp[k][j] = dp[k - 1][j] * (j + 1) (if it's not 1st maximum, then it can be any element in given range)
	+ dp[k - 1][j - 1] (becomes maximum).
	
4. This gives O(n ^ 3) time and O(n ^ 2) memory solution, which causes TLE.
5. To improve it, I want to prove that I can do all operations at the same time.
In other words, I want to make dp array outside of main cycle, and to not process it until the end of cycle.
But, I still set initial value dp[i][max(a[0], a[1], ..., a[i - 1]] = a[i] - 1 for every i in range [0; n - 1].

6. This give O(n ^ 2) time and O(n ^ 2) memory, which causes MLE.
7. To improve it again, I want to notice that I don't access elements before previous column.
Then, I only need to keep 2 columns: current and previous.
To set initial values, I can do that once I reach this column.

This give O(n ^ 2) time and O(n) memory, which gives AC if it's coded properly.
**/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
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
const int mod = 1e6 + 7;

void run() {
    int n;
    get n;
    int ans = 1;
    int lim = 0;

    int a[n];

    rep(i, 0, n)
        a[i] = getInt() - 1;

    int dp[n];
    rep(i, 0, n)
        dp[i] = 0;

    rep(i, 1, n) {
        int nxt[n];
        rep(j, 0, n) {
            nxt[j] = (dp[j] * (j + 1)) % mod;
            if (j) {
                nxt[j] = (nxt[j] + dp[j - 1]) % mod;
                swap(dp[j - 1], nxt[j - 1]);
            }
        }

        dp[lim] = (dp[lim] + a[i]) % mod;
        lim = max(a[i], lim);
    }

    rep(j, 0, n)
        ans = (ans + dp[j]) % mod;

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
