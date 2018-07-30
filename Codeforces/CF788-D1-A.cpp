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
    int a[n];
    rep(i, 0, n)
        get a[i];

    int b[n - 1];
    rep(i, 0, n - 1)
        b[i] = abs(a[i] - a[i + 1]);

    int s1 = -inf, s2 = -inf;

    int cur = 0;
    rep(i, 0, n - 1) {
        if (i % 2)
            cur -= b[i];
        else
            cur += b[i];

        cur = max(cur, 0ll);
        s1 = max(s1, cur);
    }

    cur = 0;
    rep(i, 1, n - 1) {
        if (i % 2 == 0)
            cur -= b[i];
        else
            cur += b[i];

        cur = max(cur, 0ll);
        s2 = max(s2, cur);
    }

    put max(s1, s2);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}