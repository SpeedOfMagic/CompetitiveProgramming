/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
const int mod = 1e9 + 7;

int solve(str r) {
    if (sz(r) == 1)
        return r[0] - '0' + 1;

    int ans = 0;

    str dd = "9";
    while (sz(dd) + 1 < sz(r))
        dd += "9";
    ans += solve(dd);

    int n = sz(r);

    int dp[n][10];
    rep(i, 0, n) {
        int prob1 = (i ? r[i - 1] - '0' : -1);

        if (prob1 > r[i] - '0')
            break;

        rep(j, 0, 10) {
            dp[i][j] = 0;
            if (r[i] - '0' < j || (i + 1 < n && r[i] - '0' == j) || (i == 0 && j == 0))
                continue;

            if (prob1 <= j)
                dp[i][j] = 1;
        }

        rep(p, i + 1, n)
            rep(j, 0, 10) {
                dp[p][j] = 0;
                rep(k, 0, j + 1)
                    dp[p][j] = (dp[p][j] + dp[p - 1][k]) % mod;
            }

        rep(j, 0, 10)
            ans = (ans + dp[n - 1][j]) % mod;
    }

    return ans;
}

int good(str a) {
    char pr = '0';
    for (char i : a)
        if (i >= pr)
            pr = i;
        else
            return 0;
    return 1;
}

void run() {
    str a, b;
    read(a, b);
    put (solve(b) - solve(a) + good(a) + mod) % mod;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
