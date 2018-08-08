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
    int n, m;
    read(n, m);
    int a[n];
    int b[m];
    rep(i, 0, n)
        get a[i];
    rep(i, 0, m)
        get b[i];

    int ans[n][m];
    rep(i, 0, n)
        rep(j, 0, m)
            ans[i][j] = 0;

    rep(bit, 0, 31) {
        vint row, col;
        rep(i, 0, n)
            if (a[i] & (1 << bit))
                row.pb(i);

        rep(i, 0, m)
            if (b[i] & (1 << bit))
                col.pb(i);

        int p = 0;
        rep(i, 0, sz(row)) {
            if (p == sz(col)) {
                if (i + 1 < sz(row)) {
                    ans[row[i]][0] |= (1 << bit);
                    i++;
                    ans[row[i]][0] |= (1 << bit);
                } else {
                    put "NO";
                    return;
                }
            } else {
                ans[row[i]][col[p]] |= (1 << bit);
                p++;
            }
        }

        for (; p < sz(col); p++) {
            if (p + 1 < sz(col)) {
                ans[0][col[p]] |= (1 << bit);
                p++;
                ans[0][col[p]] |= (1 << bit);
            } else {
                put "NO";
                return;
            }
        }
    }

    put "YES";
    eol;
    rep(i, 0, n) {
        rep(j, 0, m)
            print(ans[i][j]);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}