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
#if 1  //FileIO
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
char curFlag = 'A'; void flag() {put curFlag++ << endl;}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        put "Case #" << test << ": ";
        int n, k;
        read(n, k);
        int opt = k;
        int ans = 0;
        int cur = k - 1;
        v<vint> E;
        for (int i = 1; i < n; i++) {
            if (cur == 1) {
                E.pb({i, n, cur});
                ans += cur;
                break;
            }
            E.pb({i, i + 1, cur});
            ans += cur;
            cur--;
        }
        if (opt >= ans) {
            put 0;
            eol;
            put 1;
            eol;
            put "1 " << n << " 1" << endl;
            continue;
        }

        put ans - opt;
        eol;
        put sz(E) + 1;
        eol;
        for (vint i : E)
            put i[0] << " " << i[1] << " " << i[2] << endl;
        put "1 " << n << " " << k << endl;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
