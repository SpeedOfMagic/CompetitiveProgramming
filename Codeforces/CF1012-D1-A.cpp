/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
typedef long double ld;
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
    int n;
    get n;
    int a[n * 2];
    rep(i, 0, n * 2)
        get a[i];
    sort(a, a + n * 2);

    int ans = inf;
    rep(i, n - 1, n * 2) {
        if (i == n - 1)
            ans = min(ans, (a[n - 1] - a[0]) * (a[n * 2 - 1] - a[n]));
        else if (i == n * 2 - 1)
            ans = min(ans, (a[i] - a[i - (n - 1)]) * (a[n * 2 - 1 - (n - 1) - 1] - a[0]));
        else
            ans = min(ans, (a[i] - a[i - (n - 1)]) * (a[n * 2 - 1] - a[0]));
    }
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}