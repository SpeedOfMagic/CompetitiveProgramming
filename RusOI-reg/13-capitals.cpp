/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
An unweighted tree with n (1 <= n <= 1e5) vertexes and integer d (1 <= d <= n) are given.
Find amount of triples (i, j, k) such dist(i, j) = dist(j, k) = dist(i, k) = d.
*/
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
template<typename T> using v = vector<T>;
//template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
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
#if 1  //FileIO
const string fileName = "capitals";
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
/*
Solution:
It can be simplified to the next problem: for every vertex: suppose it's a root of the tree.
We want to build an array, where i-th value means: "Amount of vertexes whose distance = d/2 from root in i-th
subtree of the root" (if d is odd then answer to the original problem = 0).
After that we'll find sum of multiplication of all triples, then sum all these sums, which is the answer to original one.

Suppose vertex 1 is root. Then it's possible to find amount of vertexes whose distance = d/2 for every subtree
of every vertex by using binary lifting. What's left is to find amount of vertexes that are not in the subtree.

By using centroid decomposition we can find amount of all vertexes whose distance = d/2 from every other ones. Then it's easy
to find amount of vertexes that are not in the subtree.

It's also possible to find amount of vertexes that are not in the subtree by using dsu on trees.

To find sum of multiplication of all triples, we need to find sum of multiplication of all pairs firstly,
then repeat process used to find the sum of multiplication of all pairs.
*/
//code goes here
const int N = 1e5 + 1;
vector<int> t[N];
int siz[N];
bitset<N> added;
int d;

int calcSize(int cur, int p) {
    siz[cur] = 1;
    for (int i : t[cur])
        if (!added.test(i) && i != p)
            siz[cur] += calcSize(i, cur);
    return siz[cur];
}

map<int, int> dist[N];
map<int, int> tot;
int vals[N];
void setDist(int cur, int p, int h, int ind) {
    if (h > d)
        return;
    dist[ind][h]++;
    tot[h]++;
    for (int i : t[cur])
        if (!added.test(i) && i != p)
            setDist(i, cur, h + 1, ind);
}

void getDist(int cur, int p, int h, int ind) {
    if (h > d)
        return;
    vals[cur] += tot[d - h] - dist[ind][d - h];
    if (d == h)
        vals[cur]++;
    for (int i : t[cur])
        if (!added.test(i) && i != p)
            getDist(i, cur, h + 1, ind);
}

void solve(int cur) {
    tot.clear();
    int p = 0;
    for (int i : t[cur])
        if (!added.test(i)) {
            dist[p].clear();
            setDist(i, -1, 1, p++);
        }
    vals[cur] += tot[d];
    p = 0;
    for (int i : t[cur])
        if (!added.test(i))
            getDist(i, -1, 1, p++);
}

void find_centroid(int cur) {
    int lim = calcSize(cur, -1) / 2;
    int pr = -1;
    for (bool again = 1; again;) {
        again = 0;
        for (auto i : t[cur]) {
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
            find_centroid(i);
}

int h[N];
const int M = 17;
int kthAncestor[N][M];

int getKthAncestor(int v, unsigned int distance) {
    for (int k = 0; distance && k < M; k++, distance >>= 1)
        if (distance & 1)
            v = kthAncestor[v][k];
    return v;
}

vint pathsInSubtree[N];

inline void precalc(int cur = 1, int p = -1) {
    h[cur] = (p != -1) ? (h[p] + 1) : 0;
    int D = p;
    for (int k = 0; D != -1; k++) {
        kthAncestor[cur][k] = D;
        D = kthAncestor[D][k];
    }

    if (h[cur] >= d)
        pathsInSubtree[getKthAncestor(cur, d)].back()++;

    for (int i : t[cur]) {
        pathsInSubtree[cur].pb(0);
        if (i != p)
            precalc(i, cur);
    }
}

void run() {
    int n;
    memset(vals, 0, sizeof vals);
    memset(pathsInSubtree, 0, sizeof pathsInSubtree);
    memset(kthAncestor, -1, sizeof kthAncestor);
    read(n, d);
    if (d % 2) {
        put 0;
        return;
    }
    d /= 2;
    rep(i, 1, n) {
        int v, u;
        read(v, u);
        t[v].pb(u);
        t[u].pb(v);
    }
    find_centroid(1);
    longlong ans = 0;
    precalc();
    rep(i, 1, n + 1) {
        int s = 0;
        for (int j : pathsInSubtree[i])
            s += j;
        pathsInSubtree[i].pb(vals[i] - s);
        if (sz(pathsInSubtree[i]) < 3)
            continue;
        longlong allSquares = 0;
        for (longlong j : pathsInSubtree[i]) {
            //print(j);
            allSquares += (vals[i] - j) * j;
        }
        allSquares /= 2;
        //eol;
        for (longlong j : pathsInSubtree[i])
            ans += (allSquares - (vals[i] - j) * j) * j;
    }
    put ans / 3;
}
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(15); run(); return 0;}
