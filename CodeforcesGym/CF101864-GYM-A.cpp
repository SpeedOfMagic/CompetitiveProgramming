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
        put "Case " << test << ": ";
        int x, l, n;
        read(x, l, n);

        int q = n - l + 1;
        int p = 0;
        if (l < x)
            p += (x - l);
        if (x % 2) {
            int d = x / 2;
            int k = 1;
            while (k <= d)
                k *= 2;
            while (k + d <= n) {
                if (k + d >= l)
                    p++;
                k *= 2;
            }
        }

        int g = __gcd(p, q);
        p /= g;
        q /= g;
        put p << "/" << q << endl;
    }

    /** 2^N: 1
    1: 1
    2: 1
    3: 3
    4: 1
    5: 3
    6: 5
    7: 7
    8: 1
    9: 3
    10: 5
    11: 7
    12: 9
    13: 11
    14: 13
    15: 15
    16: 1
    20: 9
    30: 29
    31: 31
    32: 1
    x: (x - msb(x)) * 2 + 1

    **/
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}