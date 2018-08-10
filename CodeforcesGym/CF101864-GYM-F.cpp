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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        put "Case " << test << ":";
        eol;
        int n, k, q;
        read(n, k, q);
        int ans = 1;
        set<int> cur;
        rep(i, 0, k)
            cur.insert(i + 1);
        cur.insert(0);
        cur.insert(n + 1);
        for (; q; q--) {
            int x, y;
            read(x, y);
            bool l = cur.count(x - 1), r = cur.count(x + 1);
            if (l && r)
                ans++;
            else if (!l && !r)
                ans--;
            cur.erase(x);
            l = cur.count(y - 1);
            r = cur.count(y + 1);
            if (l && r)
                ans--;
            else if (!l && !r)
                ans++;
            cur.insert(y);
            put ans;
            eol;
        }
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}