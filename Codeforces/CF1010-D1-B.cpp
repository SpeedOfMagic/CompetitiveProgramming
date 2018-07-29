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
    int m, n;
    read(m, n);

    int seq[n];
    rep(i, 0, n) {
        put 1;
        eol;
        int d;
        get d;
        if (d == 0)
            return;
        else {
            if (d == 1)
                seq[i] = 1;
            else
                seq[i] = 0;
        }
    }

    int p = 0;
    int l = 0, r = m + 1;
    while (l + 1 < r) {
        int mid = (l + r) / 2;
        put mid;
        eol;
        int d;
        get d;
        if (d == 0)
            return;
        else {
            if (seq[p] == 0)
                d = -d;
            if (d == 1)
                l = mid;
            else
                r = mid;
        }
        p = (p + 1) % n;
    }

    put l;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}