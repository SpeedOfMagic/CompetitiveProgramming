/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. If amount of cameras >= n then obviously answer is 1. => p + q <= n.
2. It's obvious that if it's possible to place cameras with range w,
then it's also possible to do the same, but with range w + 1, =>
I can find the answer by binary search.
Suppose I have some value w and I want to check if it's possible to place cameras.

3. I can do that with dp. Suppose dp[i][j] means
"Minimum amount of large cameras that need to be placed to cover events #1 - #i,
while using <= j small cameras".
4. To calculate values efficiently, I want to declare 3 pointers:
1st one `i` is main one, 2nd pointer `p1` is such that a[i] - a[p1] < w and p1 is minimized;
3rd pointer `p2` is such that a[i] - a[p1] < 2 * w and p2 is minimized;
5. Then, dp[i][j] = min(dp[p1 - 1][j - 1], dp[p2 - 1][j] + 1).

6. The only thing that's left is to find minimum in final column dp[n - 1],
and check if result is <= q.
7. If yes, then r = w; otherwise l = w.

Time complexity: O(n * min(p, n) * log(MAX)).
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

void run() {
    int n, p, q;
    read(n, p, q);

    int a[n];
    rep(i, 0, n)
        get a[i];
    sort(a, a + n);

    if (p + q >= n) {
        put 1;
        return;
    }

    int l = 0, r = inf;
    while (l + 1 < r) {
        int w = (l + r) / 2;

        int dp[n][p + 1];

        int pointerForP = 0, pointerForQ = 0;
        rep(i, 0, n) {
            while (a[i] - a[pointerForP] >= w)
                pointerForP++;
            while (a[i] - a[pointerForQ] >= 2 * w)
                pointerForQ++;

            //debug(w, i, pointerForP, pointerForQ);

            rep(j, 0, p + 1)
                if (j) {
                    if (pointerForP == 0)
                        dp[i][j] = 0;
                    else if (pointerForQ == 0)
                        dp[i][j] = min(dp[pointerForP - 1][j - 1], 1ll);
                    else
                        dp[i][j] = min(dp[pointerForP - 1][j - 1], dp[pointerForQ - 1][j] + 1);
                } else {
                    if (pointerForQ == 0)
                        dp[i][j] = 1;
                    else
                        dp[i][j] = dp[pointerForQ - 1][j] + 1;
                }
        }

        int mn = inf;
        rep(i, 0, p + 1)
            mn = min(mn, dp[n - 1][i]);

        if (mn > q)
            l = w;
        else
            r = w;
    }

    put r;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
