/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60672
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
    int n, m, k;
    read(n, m, k);
    int a[n][m];
    rep(i, 0, n)
        rep(j, 0, m)
            get a[i][j];

    map<int, int> grid[n][m];

    int mid = ((n - 1) + (m - 1)) / 2;
    map<int, int> pos;
    for (int mask = 0; mask < (1 << mid); mask++) {
        int r = 0, c = 0;
        int val = a[r][c];
        bool valid = 1;
        rep(i, 0, mid) {
            if (mask & (1 << i)) {
                r++;
                if (r == n) {
                    valid = 0;
                    break;
                }
            } else {
                c++;
                if (c == m) {
                    valid = 0;
                    break;
                }
            }
            val ^= a[r][c];
        }

        if (valid)
            grid[r][c][val]++;
    }

    int ans = 0;
    for (int mask = 0; mask < (1 << ((n - 1) + (m - 1) - mid)); mask++) {
        int r = n - 1, c = m - 1;
        int val = a[r][c];
        bool valid = 1;
        rep(i, 0, ((n - 1) + (m - 1) - mid)) {
            if (mask & (1 << i)) {
                r--;
                if (r < 0) {
                    valid = 0;
                    break;
                }
            } else {
                c--;
                if (c < 0) {
                    valid = 0;
                    break;
                }
            }
            val ^= a[r][c];
        }

        val ^= a[r][c];
        if (valid)
            ans += grid[r][c][val ^ k];
    }

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}