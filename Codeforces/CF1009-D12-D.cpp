/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60630
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
int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a > b)
        swap(a, b);

    if (a > 0)
        return gcd(a, b % a);

    return b;
}
void run() {
    int n, m;
    read(n, m);

    if (m < n - 1) {
        put "Impossible";
    } else {
        v<pair<int, int>> ans;
        rep(i, 2, n + 1)
            ans.pb({1, i});

        int p = 2;
        while (sz(ans) != m && p < n) {
            for (int i = p + 1; i <= n; i++)
                if (gcd(i, p) == 1) {
                    ans.pb({p, i});
                    if (sz(ans) == m)
                        break;
                }

            p++;
        }

        if (sz(ans) == m) {
            put "Possible";
            eol;
            for (auto i : ans)
                debug(i.first, i.second);
        } else
            put "Impossible";
    }
}
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}