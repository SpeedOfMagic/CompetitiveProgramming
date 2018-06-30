/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://codeforces.com/blog/entry/53815
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
const int inf = 4611686018427387903; //2^62 - 1
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
int ppow(int a, int b) {
    if (b == 0)
        return 1 % mod;

    if (b == 1)
        return a % mod;

    int res = ppow(a, b/2);
    res = (res * res) % mod;

    if (b % 2 == 1)
        return (a * res) % mod;

    return res;
}

void run() {
    int n;
    get n;

    int a[n];
    rep(i, 0, n)
        get a[i];

    sort(a, a + n);

    const int M = 1e6 + 1;
    vint erato[M];
    rep(i, 2, M)
        for (int j = 1; j * i < M; j++)
            erato[j * i].pb(i);

    int cnt[M];
    rep(i, 1, M)
        cnt[i] = 0;

    rep(i, 0, n)
        for (int j : erato[a[i]])
            cnt[j]++;

    int ans[M];
    for (int i = M - 1; i; i--) {
        ans[i] = (ppow(2, cnt[i] - 1) * cnt[i]) % mod;

        for (int j = 2; i * j < M; j++)
            ans[i] = ((ans[i] - ans[i * j]) % mod + mod) % mod;
    }

    int res = 0;
    rep(i, 2, M)
        res = (res + (i * ans[i]) % mod) % mod;

    put res;
    eol;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
