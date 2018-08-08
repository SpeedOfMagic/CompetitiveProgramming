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
    int n, m, q;
    read(n, m, q);
    int w[n];
    rep(i, 0, n)
        get w[i];
    reverse(w, w + n);

    int M = (1 << n);
    int amount[M];
    rep(i, 0, M)
        amount[i] = 0;

    rep(i, 0, m) {
        str s;
        get s;
        int v = 0;
        rep(j, 0, n)
            v = (v << 1) | (s[j] - '0');
        amount[v]++;
    }
    int precalc[M][101];
    rep(i, 0, M)
        rep(k, 0, 101)
            precalc[i][k] = 0;

    rep(i, 0, M) {
        rep(j, 0, M) {
            int cost = 0;
            rep(k, 0, n)
                if ((i & (1 << k)) == (j & (1 << k)))
                    cost += w[k];
            if (cost <= 100)
                precalc[i][cost] += amount[j];
        }
        int s = 0;
        rep(j, 0, 101) {
            s += precalc[i][j];
            precalc[i][j] = s;
        }
    }
    //rep(i, 0, 101) print(precalc[0][i]);eol;
    for (; q; q--) {
        str t; int k;
        read(t, k);
        int v = 0;
        rep(j, 0, n)
            v = (v << 1) | (t[j] - '0');
        put precalc[v][k] << '\n';
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}