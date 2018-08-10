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
    for (; t; t--) {
        int n;
        get n;
        int a[n];
        rep(i, 0, n)
            get a[i];
        int m;
        get m;
        int c[m];
        rep(i, 0, m)
            get c[i];

        int b[m];
        rep(i, 0, m)
            b[i] = 0;

        rep(i, 0, m) {
            int s = 0;
            for (int j = 0; j < i; j++)
                if (i - j >= n)
                    continue;
                else
                    s += b[j] * a[i - j];

            b[i] = (c[i] - s) / a[0];

            /**
            c[0] = a[0] * b[0];
            c[1] = a[0] * b[1] + b[0] * a[1];
            c[2] = a[0] * b[2] + a[1] * b[1] + a[2] * b[0];
            **/
        }

        vint ans;
        rep(i, 0, m)
            ans.pb(b[i]);
        while (ans.back() == 0)
            ans.pop_back();
        put sz(ans); eol;
        for (int i : ans)
            print(i);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}