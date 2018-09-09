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
struct dsu {
    vector<int> repr;
    vector<int> siz;
    vint mn, mx;

    int _find(int a) {
        if (repr[a] == a)
            return a;
        else
            return repr[a] = _find(repr[a]);
    }

    void unite(int a, int b) {
        if (connected(a, b))
            return;

        a = _find(a);
        b = _find(b);

        if (siz[a] > siz[b])
            swap(a, b);

        repr[a] = b;

        siz[b] += siz[a];
        mn[b] = min(mn[a], mn[b]);
        mx[b] = max(mx[a], mx[b]);
    }

    bool connected(int a, int b) {
        return _find(a) == _find(b);
    }

    dsu(vint arr) {
        int n = sz(arr);
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
            mn.pb(arr[i]);
            mx.pb(arr[i]);
        }
    }
};

void run() {
    int n, m, a, b;
    read(n, m, a, b);
    vint arr(n, 0);
    v<vint> E;
    rep(i, 0, m) {
        int v, u;
        read(v, u);v--;u--;
        E.pb({v, u});
        arr[v]++;
        arr[u]++;
    }
    
    dsu d = dsu(arr);
    rep(i, 0, m)
        d.unite(E[i][0], E[i][1]);
    
    int ans = 0;
    rep(i, 0, n)
        ans += (a * d.mn[d._find(i)] < arr[i] && arr[i] < b * d.mx[d._find(i)]);
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
