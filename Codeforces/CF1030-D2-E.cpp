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
    }

    bool connected(int a, int b) {
        return _find(a) == _find(b);
    }

    dsu(int n) {
        for(int i = 0; i < n; i++) {
            repr.push_back(i);
            siz.push_back(1);
        }
    }
};

void run() {
    int n;
    get n;

    v<pair<int, int>> g[5];
    vint leads[5];
    bool con[5][5];
    memset(con, 0, sizeof(con));
    rep(i, 0, n) {
        int c1, v, c2;
        read(c1, v, c2);
        g[c1].pb({c2, v});
        g[c2].pb({c1, v});
        if (c1 != c2) {
            leads[c1].pb(v);
            leads[c2].pb(v);
        }
        con[c1][c2] = 1;
        con[c2][c1] = 1;
    }

    dsu d1(5);
    rep(i, 1, 5)
        rep(k, 1, 5)
            if (con[k][i]) 
                d1.unite(i, k);
            
    map<int, set<int>> zx;
    rep(i, 1, 5)
        zx[d1._find(i)].insert(i);
        
    v<set<int>> comp;
    for (auto i : zx)
        comp.pb(i.second);
            
    int ans = 0;
    for (set<int> i : comp) {
        int oddAmount = 0;
        int res = 0;
        for (int j : i) {
            if (sz(g[j]) % 2)
                oddAmount++;
            for (auto k : g[j])
                res += k.sc;
        }

        res /= 2;

        if (oddAmount == 4) {
            res = 0;
            for (int j : i) {
                v<pair<int, int>> toCheck = g[j];
                for (auto k : toCheck) {
                    if (j == k.fs) {continue;}
                    v<pair<int, int>> willBe;
                    rep(l, 0, sz(g[j])) {
                        if (g[j][l] == k) {
                            rep(z, 0, sz(g[j]))
                                if (z != l)
                                    willBe.pb(g[j][z]);
                            break;
                        }
                    }
//check(1);
                    g[j] = willBe;
                    willBe.clear();
                    rep(l, 0, sz(g[k.fs])) {
                        if (g[k.fs][l] == make_pair(j, k.sc)) {
                            rep(z, 0, sz(g[k.fs]))
                                if (z != l)
                                    willBe.pb(g[k.fs][z]);
                            break;
                        }
                    }
//check(2);
                    g[k.fs] = willBe;

                    dsu d2(5);
                    for (int ii : i)
                        for (auto ll : g[ii])
                            d2.unite(ll.fs, ii);
                            
                    map<int, set<int>> zx;
                    rep(ii, 1, 5)
                        zx[d2._find(ii)].insert(ii);
                        
                    v<set<int>> comp2;
                    for (auto i : zx)
                        comp2.pb(i.second);
                    
//check(3);
                    for (set<int> ii : comp2) {
                        int pos = 0;
                        for (int jj : ii)
                            for (auto kk : g[jj])
                                pos += kk.sc;
                        pos /= 2;
                        res = max(res, pos);
                    }


                    g[j].pb(k);
                    g[k.fs].pb({j, k.sc});
                }
            }
        }
        ans = max(ans, res);
    }
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}