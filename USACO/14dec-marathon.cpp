/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
// Editorial: http://usaco.org/current/data/sol_marathon_gold.html
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
#if 1  //FileIO
const string fileName = "marathon";
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
vint segTree;
int N;
int query(int l, int r, int cur = 1, int ll = 1, int rr = N) {
    //debug(l, r, cur, ll, rr);
    int mid = (ll + rr) / 2;
    if (l == ll && r == rr)
        return segTree[cur];
    else if (r <= mid)
        return query(l, r, cur * 2, ll, mid);
    else if (l > mid)
        return query(l, r, cur * 2 + 1, mid + 1, rr);
    else
        return min(query(l, mid, cur * 2, ll, mid), query(mid + 1, r, cur * 2 + 1, mid + 1, rr));
}

void update(int p, int x, int cur = 1, int ll = 1, int rr = N) {
    //debug(p, x, cur, ll, rr);
    if (ll == rr)
        segTree[cur] = x;
    else {
        int mid = (ll + rr) / 2;
        if (p <= mid)
            update(p, x, cur * 2, ll, mid);
        else
            update(p, x, cur * 2 + 1, mid + 1, rr);

        segTree[cur] = min(segTree[cur * 2], segTree[cur * 2 + 1]);
    }
}


void init(vint vals) {
    while(sz(vals) & (sz(vals) - 1))
        vals.pb(inf);

    int n = sz(vals);
    N = sz(vals);
    segTree = vint(2 * n);

    rep(i, 0, n)
        segTree[n + i] = vals[i];

    for (int i = n - 1; i; i--)
        segTree[i] = min(segTree[i * 2], segTree[i * 2 + 1]);
}

int lsb(int a) {
    return a & -a;
}

struct fenwick {
    vint fenwickTree;

    int query(int l, int r) {
        if (l != 1)
            return query(1, r) - query(1, l - 1);

        if (r == 0)
            return 0;
        else
            return fenwickTree[r] + query(l, r - lsb(r));
    }

    void update(int p, int x) {
        if (p > sz(fenwickTree))
            return;

        fenwickTree[p] += x;
        update(p + lsb(p), x);
    }

    fenwick(vint vals) {
        fenwickTree = vint(sz(vals) + 1, 0);
        rep(i, 0, sz(vals))
            update(i + 1, vals[i]);
    }
};

void run() {
    int n, q;
    read(n, q);


    int checkpointsX[n], checkpointsY[n];
    rep(i, 0, n)
        read(checkpointsX[i], checkpointsY[i]);

    vint pathLengths;
    rep(i, 1, n)
        pathLengths.pb(abs(checkpointsX[i] - checkpointsX[i - 1]) + abs(checkpointsY[i] - checkpointsY[i - 1]));

    fenwick fenwickTree = fenwick(pathLengths);

    vint ifRemoved;
    ifRemoved.pb(inf);
    rep(i, 1, n - 1)
        ifRemoved.pb(abs(checkpointsX[i - 1] - checkpointsX[i + 1]) + abs(checkpointsY[i - 1] - checkpointsY[i + 1]) -
                        (pathLengths[i - 1] + pathLengths[i]));
    ifRemoved.pb(inf);

    init(ifRemoved);

    //for (int i : ifRemoved) print(i); eol;

    for (; q; q--) {
        str s;
        get s;
        if (s == "U") {
            int i, x, y;
            read(i, x, y);
            i--;
            checkpointsX[i] = x;
            checkpointsY[i] = y;

            if (i) {
                int pathLength = abs(checkpointsX[i] - checkpointsX[i - 1]) + abs(checkpointsY[i] - checkpointsY[i - 1]);
                fenwickTree.update(i, pathLength - pathLengths[i - 1]);
                pathLengths[i - 1] = pathLength;
            }

            if (i + 1 < n) {
                int pathLength = abs(checkpointsX[i] - checkpointsX[i + 1]) + abs(checkpointsY[i] - checkpointsY[i + 1]);
                fenwickTree.update(i + 1, pathLength - pathLengths[i]);
                pathLengths[i] = pathLength;
            }

            for (int delta = -1; delta <= 1; delta++) {
                int j = delta + i;
                if (j > 0 && j + 1 < n) {
                    ifRemoved[j] = abs(checkpointsX[j - 1] - checkpointsX[j + 1]) + abs(checkpointsY[j - 1] - checkpointsY[j + 1]) -
                            (pathLengths[j - 1] + pathLengths[j]);
                    update(j + 1, ifRemoved[j]);
                }
            }

        } else {
            int l, r;
            read(l, r);

            if (l == r) {
                put 0;
            } else if (l + 1 == r) {
                put abs(checkpointsX[l - 1] - checkpointsX[r - 1]) + abs(checkpointsY[l - 1] - checkpointsY[r - 1]);
            } else put fenwickTree.query(l, r - 1) + query(l + 1, r - 1);
            eol;
        }
    }

}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
