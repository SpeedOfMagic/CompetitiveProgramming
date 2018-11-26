/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/* Simple static centroid decomposition + detection of correct () substring. */
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
template<typename T> using v = vector<T>;
//template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
typedef long long longlong;
#define int longlong
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
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
int popcount(int a) { return __builtin_popcount(a); }
//code goes here
const int N = 3e5 + 1;
vector<int> t[N]; //init me
int siz[N];
bitset<N> added;
 
int vals[N];
 
int calcSize(int cur, int p) {
    siz[cur] = 1;
    for (auto i : t[cur])
        if (!added.test(i) && i != p)
            siz[cur] += calcSize(i, cur);
    return siz[cur];
}
 
 
map<int, int> dist[N];
int p;
map<int, int> allDist;
void addDistances(int cur, int l, int r, int par = -1) {
    if (l == 0) {
        allDist[r]++;
        dist[p][r]++;
    }
    for (int i : t[cur])
        if (!added.test(i) && i != par) {
            if (vals[i] == 1)
                addDistances(i, l + 1, r, cur);
            else
                addDistances(i, max(0ll, l - 1), r + (l == 0), cur);
        }
}
 
int ans = 0;
void checkDistances(int cur, int l, int r, int par = -1) {
    if (r == 0)
        ans += allDist[l] - dist[p][l];
    for (int i : t[cur])
        if (!added.test(i) && i != par) {
            if (vals[i] == 1)
                checkDistances(i, l + (r == 0), max(0ll, r - 1), cur);
            else
                checkDistances(i, l, r + 1, cur);
        }
}
 
void solve(int cur) {
    allDist.clear();
    p = 0;
    int l = vals[cur] == 1, r = vals[cur] == -1;
    for (auto i : t[cur])
        if (!added.test(i)) {
            dist[p].clear();
            if (vals[i] == 1)
                addDistances(i, l + 1, r, cur);
            else
                addDistances(i, max(0ll, l - 1), r + (l == 0), cur);
            p++;
        }
 
    if (vals[cur] == -1)
        allDist[1]++;
    else
        ans += allDist[0];
    p = 0;
    for (auto i : t[cur])
        if (!added.test(i)) {
            checkDistances(i, vals[i] == 1, vals[i] == -1);
            p++;
        }
}
 
void find_centroid(int cur) {
    int lim = calcSize(cur, -1) / 2;
    int pr = -1;
    for (bool again = 1; again;) {
        again = 0;
        for (auto i : t[cur])
			if (!added.test(i) && i != pr && siz[i] > lim) {
                pr = cur;
				cur = i;
                again = 1;
                break;
            }
    }
    added.set(cur);
    solve(cur);
 
    for (auto i : t[cur])
        if (!added.test(i))
            find_centroid(i);
}
 
void run() {
    int n;
    get n;
    str s;
    get s;
    rep(i, 1, n + 1)
        if (s[i - 1] == '(')
            vals[i] = 1;
        else
            vals[i] = -1;
    rep(i, 1, n) {
        int v, u;
        read(v, u);
        t[v].pb(u);
        t[u].pb(v);
    }
    find_centroid(1);
    put ans;
}
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(15); run(); return 0;}