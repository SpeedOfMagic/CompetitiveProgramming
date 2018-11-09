/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/* Solution
1. It can be solved with divide & conquer approach by using centroid decomposition
2. 
*/
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
template<typename T> using v = vector<T>;
//template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
typedef long long ll;
//#define int ll
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define all(a) (a).begin(), (a).end()
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
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 2e5 + 1;
vint t[N];
int siz[N];
int val[N];
bitset<N> added;

const int M = 18;
int kthAncestor[N][M];
ll add[N], reduce[N];
int h[N];

inline void precalc(int cur = 1, int p = -1) {
    if (p == -1)
        h[cur] = 1;
    else
        h[cur] = h[p] + 1;
    int d = p;
    for (int k = 0; d != -1; k++) {
        kthAncestor[cur][k] = d;
        d = kthAncestor[d][k];
    }

    for (int i : t[cur])
        if (i != p)
            precalc(i, cur);
}

inline int lca(int v, int u) {
    if (h[v] > h[u])
        swap(v, u);

    for (int k = 0, d = h[u] - h[v]; d; k++, d >>= 1)
        if (d & 1)
            u = kthAncestor[u][k];

    for (int k = M - 1; u != v;)
        if (kthAncestor[u][k] != kthAncestor[v][k] || !k) {
            u = kthAncestor[u][k];
            v = kthAncestor[v][k];
        } else
            k--;
    return u;
}

inline int getKthAncestor(int v, unsigned int distance) {
    int k = 0;
    while (distance && k < M) {
        if (distance & 1)
            v = kthAncestor[v][k];
        distance >>= 1;
        k++;
    }

    return v;
}

inline void addQuery(int v, int u, int w) {
    int l = lca(v, u);
    if (h[v] > h[u])
        swap(v, u);
    if (l == v) {
        add[u] += w;
        reduce[v] += w;
    } else {
        add[v] += w;
        add[u] += w;
        reduce[l] += w;
        add[l] -= w;
    }
}

inline int calcSize(int cur, int p = -1) {
    siz[cur] = 1;
    for (int i : t[cur])
        if (i != p && !added.test(i))
            siz[cur] += calcSize(i, cur);
    return siz[cur];
}

ll ans[N];

const int L = 1 << 20;
int has[L], version[L];
inline int getHas(int ind, int v) {
    if (version[ind] != v) {
        has[ind] = 0;
        version[ind] = v;
    }
    return has[ind];
}
int local[L], versLocal[L];
inline int getLocal(int ind, int v) {
    if (versLocal[ind] != v) {
        local[ind] = 0;
        versLocal[ind] = v;
    }
    return local[ind];
}

int init, iinit, ptr = 0;

inline void dfs(int cur, int p, int value, int todo) {
    if (todo == 2) {
        int amount = -getLocal(value, ptr);
        rep(j, 0, 20)
            amount -= getLocal(value ^ (1 << j), ptr);

        if (amount) {
            //print(cur, init, amount); eol;
            addQuery(init, cur, amount);
            ans[iinit] += amount;
        }
    } else if (todo) {
        int amount = getHas(value, iinit);
        if ((value & (value - 1)) == 0) {
            amount++;
            ans[iinit]++;
        }
        rep(j, 0, 20)
            amount += getHas(value ^ (1 << j), iinit);

        if (amount) {
            //print(cur, init, amount); eol;
            addQuery(init, cur, amount);
            ans[iinit] += amount;
        }
    } else {
        getHas(value, iinit);
        has[value]++;
        getLocal(value, ptr);
        local[value]++;
    }
    for (int j : t[cur])
        if (j != p && !added.test(j))
            dfs(j, cur, value ^ val[j], todo);
}

void find_centroid(int cur = 1) {
    calcSize(cur);
    int lim = siz[cur] / 2;
    int pr = -1;
    for (bool again = 1; again; ) {
        again = 0;
        for (int i : t[cur])
            if (i != pr && !added.test(i) && siz[i] > lim) {
                pr = cur;
                cur = i;
                again = 1;
                break;
            }
    }
    //print(cur); eol;
    iinit = cur;
    added.set(cur);
    for (int i : t[cur])
        if (!added[i]) {
            init = i;
            dfs(i, cur, val[i], 0);
            dfs(i, cur, val[i] ^ val[cur], 2);
            ptr++;
        }

    for (int i : t[cur])
        if (!added[i]) {
            init = i;
            dfs(i, cur, val[cur] ^ val[i], 1);
        }

    for (int i : t[cur])
        if (!added[i])
            find_centroid(i);
    ans[cur] /= 2;
}

inline ll dfs2(int cur = 1, int p = -1) {
    ll value = add[cur];
    for (int i : t[cur])
        if (i != p)
            value += dfs2(i, cur);
    ans[cur] += value;
    return value - reduce[cur];
}

inline void run() {
    memset(ans, 0, sizeof ans);
    memset(version, -1, sizeof version);
    memset(versLocal, -1, sizeof versLocal);
    memset(add, 0, sizeof add);
    memset(kthAncestor, -1, sizeof kthAncestor);
    memset(reduce, 0, sizeof reduce);

    int n;
    get n;
    rep(i, 1, n) {
        int v = i, u = i + 1;
        read(v, u);
        t[v].pb(u);
        t[u].pb(v);
    }
    precalc();
    str s;
    get s;
    rep(i, 1, n + 1)
        //val[i] = 1;
        val[i] = 1 << (s[i - 1] - 'a');
    find_centroid();
    dfs2();

    rep(i, 1, n + 1)
        print(ans[i] + 1);
}

signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(15); run(); return 0;}