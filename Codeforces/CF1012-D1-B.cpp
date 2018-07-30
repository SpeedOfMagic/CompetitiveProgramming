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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

struct dsu {
    vector<int> repr;
    vector<int> siz;

    int fin(int a) {
        if (repr[a] == a)
            return a;
        else
            return repr[a] = fin(repr[a]);
    }

    void unite(int a, int b) {
		if (connected(a, b))
			return;

        a = fin(a);
        b = fin(b);

        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
    }

    bool connected(int a, int b) {
        return fin(a) == fin(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }
};

void run() {
    int n, m, q;
    read(n, m, q);

    dsu d = dsu(n);
    vint el[n];
    vint invEl[m];

    rep(i, 0, q) {
        int r, c;
        read(r, c);
        el[r - 1].pb(c - 1);
        invEl[c - 1].pb(r - 1);
    }

    int pen = 0;
    rep(i, 0, m)
        if (sz(invEl[i]) == 0)
            pen++;
        else
            rep(j, 1, sz(invEl[i]))
                d.unite(invEl[i][j], invEl[i][j - 1]);

    set<int> pos;
    rep(i, 0, n)
        pos.insert(d.fin(i));

    put sz(pos) - 1 + pen;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}