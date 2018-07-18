/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://apio-olympiad.org/2008/solutions.pdf
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
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
    int n, m, k;
    read(n, m, k);
    n++;
    dsu gConcrete = dsu(n);
    v<pair<int, int>> edgesCobblestone, edgesConcrete;
    rep(i, 0, m) {
        int v, u;
        read(v, u);
        int d;
        get d;
        if (d) {
            gConcrete.unite(v, u);
            edgesConcrete.pb({v, u});
        } else
            edgesCobblestone.pb({v, u});
    }

    v<pair<int, int>> opt;
    int needToAdd = k;


    dsu gCobblestone = dsu(n);

    v<vint> ans;

    for (pair<int, int> i : edgesCobblestone) {
        if (gCobblestone.connected(i.first, i.second))
            continue;
        else if (gConcrete.connected(i.first, i.second))
            opt.pb(i);
        else {
            needToAdd--;
            ans.pb({i.first, i.second, 0});
            gConcrete.unite(i.first, i.second);
            gCobblestone.unite(i.first, i.second);
        }
    }

    for (pair<int, int> i : opt) {
        if (needToAdd == 0)
            break;

        if (!gCobblestone.connected(i.first, i.second)) {
            needToAdd--;
            ans.pb({i.first, i.second, 0});
            gCobblestone.unite(i.first, i.second);
        }
    }


    if (needToAdd != 0) {
        put "no solution";
    } else {
        int leftToAdd = ((n-1) - 1) - k;

        for (pair<int, int> i : edgesConcrete) {
            if (!gCobblestone.connected(i.first, i.second)) {
                leftToAdd--;
                ans.pb({i.first, i.second, 1});
                gCobblestone.unite(i.first, i.second);
            }
        }

        if (leftToAdd != 0)
            put "no solution";
        else
            for (vint i : ans)
                debug(i[0], i[1], i[2]);

    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}