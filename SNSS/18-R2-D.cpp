/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
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
int n;
/**
(0; 0) (0; 1) (0; 2)
(1; 0) (1; 1) (1; 2)
(2; 0) (2; 1) (2; 2)
**/
v<vint> rot(v<vint> mat) {
    v<vint> res(n, vint(n));
    for (int i = 0; i < n / 2 + n % 2; i++) {
        int cr = i, cc = i, pr = i, pc = n - i - 1;
        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = mat[pr][pc];
            cc++;
            pr++;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = mat[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = mat[pr][pc];
            cr++;
            pc--;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = mat[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = mat[pr][pc];
            cc--;
            pr--;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = mat[pr][pc];

        for (int j = 0; j < n - i * 2 - 1; j++) {
            res[cr][cc] = mat[pr][pc];
            cr--;
            pc++;
            //debug(cr, cc, pr, pc);
        }
        res[cr][cc] = mat[pr][pc];
    }

    return res;
}

void run() {
    get n;
    v<vint> mat(n, vint(n));
    rep(i, 0, n)
        rep(j, 0, n)
            get mat[i][j];
    while (1) {
        rep(i, 1, n)
            if (mat[i - 1][0] > mat[i][0])
                goto nxt;

        rep(j, 1, n)
            rep(i, 0, n)
                if (mat[i][j - 1] > mat[i][j])
                    goto nxt;

        rep(i, 0, n)
            rep(j, i + 1, n)
                rep(k, 0, n)
                    if (mat[i][k] >= mat[j][k])
                        goto nxt;

        rep(i, 0, n) {
            rep(j, 0, n)
                print(mat[i][j]);
            eol;
        }
    return;

        nxt:;
        mat = rot(mat);
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
