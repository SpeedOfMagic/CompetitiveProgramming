/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
Undirected weighted graph with n vertices and m edges (1 <= n, m <= 10^5) is given. 
You may choose any edges, and call them autobans. Then, their weight is increased c (1 <= c <= 1000) times.
Then, you need to find and print subset of edges such:
	1. Sum of weights of all edges in subset <= k (1 <= k <= 10^9);
	2. Graph, containing only those edges, and all n vertices, is connected;
	3. Amount of chosen autobans is maximized.
Or determine if it's impossible.

Solution:
1. It's needed to find, if it's possible to find such subset of edges without autobans.
It can be done by simple MST search.
2. It's needed to proof that for every possible MST in graph there is optimal answer that contains it.
3. Let's name the price of each edge to become autoban. It's weight * (c - 1) for every edge in chosen MST,
and weight * c for every other edge.
Then, it's needed to find maximum subset of those edges with price <= k - [weight of MST],
which may be done by sorting and greedy algorithm.

Time complexity: O(m log m).
*/
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
const string fileName = "jump";
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
const int N = 1e5 + 1;
int repr[N], siz[N];
int find(int a) {
    if (a == repr[a])
        return a;
    else
        return repr[a] = find(repr[a]);
}

void unite(int a, int b) {
    a = find(a);
    b = find(b);
    if (siz[a] > siz[b])
        swap(a, b);

    repr[a] = b;
    siz[b] += siz[a];
}

bool connected(int a, int b) {
    return find(a) == find(b);
}

void run() {
    int n, m, k, c;
    read(n, m, k, c);
    n++;
    rep(i, 1, n) {
        repr[i] = i;
        siz[i] = 1;
    }

    vint edg[m];
    rep(i, 0, m) {
        int v, u, l;
        read(v, u, l);
        edg[i] = vint({l, v, u, i});
    }

    sort(edg, edg + m);
    int tot = 0;
    v<vint> chose;
    rep(i, 0, m)
        if (!connected(edg[i][1], edg[i][2])) {
            //debug(edg[i][1], edg[i][2]);
            unite(edg[i][1], edg[i][2]);
            chose.pb(edg[i]);
            tot += edg[i][0];
        }
    if (siz[find(1)] != n - 1) {
        put "Impossible";
        return;
    }

    if (k >= tot) {
        k -= tot;
        vint ans1, ans2;

        bool used[m];
        rep(i, 0, m)
            used[i] = 0;
        for (vint i : chose)
            used[i[3]] = 1;

        pair<int, int> price[m];
        rep(i, 0, m)
            price[i].second = i;
        for (vint i : edg) {
            if (used[i[3]]) {
                price[i[3]].first = i[0] * (c - 1);
            } else {
                price[i[3]].first = i[0] * c;
            }
        }

        sort(price, price + m);

        rep(i, 0, m) {
            if (price[i].first <= k) {
                k -= price[i].first;
                ans2.pb(price[i].second + 1);
            } else {
                if (used[price[i].second])
                    ans1.pb(price[i].second + 1);
            }
        }

        print(sz(ans1), sz(ans2)); eol;
        for (int i : ans1)
            print(i);
        eol;
        for (int i : ans2)
            print(i);
    } else
        put "Impossible";
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}