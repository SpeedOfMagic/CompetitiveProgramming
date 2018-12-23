/* Solution: solve queries offline by applying them to corresponding vertexes,
then processing them by using static centroid decomposition
*/
/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
typedef long long longlong;
//#define int longlong
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
//code goes here
const int N = 3e5 + 1;
const int Q = 1e5 + 1;
longlong ans[Q];
v<pair<int, int>> queries[N];
vector<int> t[N];
int siz[N];
bitset<N> added;

inline int calcSize(int cur, int p) {
    siz[cur] = 1;
    for (int i : t[cur])
        if (!added.test(cur) && i != p)
            siz[cur] += calcSize(i, cur);
    return siz[cur];
}

int vals[N];
v<longlong> all[N];
int version[N];
int curVersion = 0;
inline void check(int pos) {
    if (curVersion > version[pos]) {
        all[pos] = {inf, -1, inf};
        version[pos] = curVersion;
    }
}

void make(int cur, int sub, int p, int dist, longlong motku) {
    check(dist);
    if (all[dist][0] > motku) {
        if (sub == all[dist][1])
            all[dist] = {motku, sub, all[dist][2]};
        else
            all[dist] = {motku, sub, all[dist][0]};
    } else if (all[dist][2] > motku && all[dist][1] != sub)
        all[dist] = {all[dist][0], all[dist][1], motku};

    for (int i : t[cur])
        if (!added.test(i) && i != p)
            make(i, sub, cur, dist + 1, motku + vals[i]);
}

void process(int cur, int sub, int p, int dist, longlong motku) {
    for (auto i : queries[cur]) {
        int need = i.fs - dist;
        if (need < 0)
            continue;
        check(need);
        longlong tot = all[need][0];
        if (all[need][1] == sub)
            tot = all[need][2];
        if (tot != inf) {
            tot += motku;
            if (ans[i.sc] == -1 || ans[i.sc] > tot)
                ans[i.sc] = tot;
        }
    }
    for (int i : t[cur])
        if (!added.test(i) && i != p)
            process(i, sub, cur, dist + 1, motku + vals[i]);
}

inline void solve(int cur) {
    curVersion++;
    int p = 0;
    for (int i : t[cur])
        if (!added.test(i))
            make(i, p++, cur, 1, vals[cur] + vals[i]);
    p = 0;
    check(0);
    all[0] = {vals[cur], -2, inf};
    for (int i : t[cur])
        if (!added.test(i))
            process(i, p++, cur, 1, vals[i]);
    for (auto i : queries[cur]) {
        int need = i.fs;
        check(need);
        longlong tot = all[need][0];
        if (tot != inf)
            if (ans[i.sc] == -1 || ans[i.sc] > tot)
                ans[i.sc] = tot;
    }
}

void make_centroid(int cur = 1) {
    int lim = calcSize(cur, -1) / 2;
    int pr = -1;
    for (bool again = 1; again; ) {
        again = 0;
        for (int i : t[cur]) {
            if (!added.test(i) && i != pr && siz[i] > lim) {
                pr = cur;
                cur = i;
                again = 1;
                break;
            }
        }
    }

    added.set(cur);
    solve(cur);
    for (int i : t[cur])
        if (!added.test(i))
            make_centroid(i);
}

void run() {
    memset(version, -1, sizeof version);
    int n;
    get n;
    rep(i, 1, n + 1)
        get vals[i];
    rep(i, 1, n) {
        int v, u;
        read(v, u);
        t[v].pb(u);
        t[u].pb(v);
    }

    int q;
    get q;
    memset(ans, -1, sizeof ans);
    for (int z = 0; z < q; z++) {
        int u, K;
        read(u, K);
        queries[u].pb({K, z});
    }
    make_centroid(1);
    rep(i, 0, q)
        put ans[i] << '\n';
}
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run(); return 0;}
