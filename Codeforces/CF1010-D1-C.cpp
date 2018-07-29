/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
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
    int n, k;
    read(n, k);
    int a[n];
    rep(i, 0, n)
        get a[i];
    rep(i, 0, n)
        a[i] %= k;
        
    int g = 0;
    rep(i, 0, n)
        g = __gcd(a[i], g);
    
    
    map<int, int> pos;
    pos[__gcd(g, k)] = g;


    bool ans[k];
    rep(i, 0, k)
        ans[i] = 0;
    ans[0] = 1;
    int tot = 1;
    for (auto i : pos) {
        int gg = i.first;
        int cur = i.second;
        rep(j, 0, k / gg + 2) {
            if (ans[cur] == 0)
                tot++;
            ans[cur] = 1;
            cur = (cur + i.second) % k;
        }
    }

    vint res;
    rep(i, 0, k)
        if (ans[i])
            res.pb(i);
    put sz(res);
    eol;
    for (int i : res)
        print(i);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}