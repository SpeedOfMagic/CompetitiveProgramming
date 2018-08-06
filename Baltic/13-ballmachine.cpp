/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. Since input is correct, then amount of added balls will not exceed n + amount of removed balls.
And, since amount of removed balls < q, then
I can process each added ball separately, because amortized amount fits in constraints.

2. I want to calculate order in which all balls will go into the tree.
For that I need to find minimum in each subtree, which can be done by simple dp on trees.
Order will be kept in form {time, index} in set.

3. So, every time I need to add a ball, I pull first element from set, and mark index.
It works in O(log n) time for each ball, and O((n + q) * log n) time in total, because of amortized analysis.

4. Now, I need to remove ball optimally.
Notice that, when ball removes, his ancestor takes this place, ancestor's ancestor takes ancestor's place,
and it keeps going until final ancestor's ancestor doesn't contain ball.
And that final ancestor becomes empty.
In other words, if instead I'll move that final ancestor to place when ball removes, result will be the same.

5. So now, I need to find least ancestor, that doesn't contain ball. For that I want to calculate kthAncestor
array, where kthAncestor[i][j] means number of vertex, who is (1 << j) ancestor of i. It can be done with dp.

6. After that I can find needed ancestor by going all possible kthAncestor and updating vertex
if I find one that contains ball. When I find this ancestor, I'll unmark it and add in set, which was mentioned in 2.

Time complexity: O((n + q) log n).
**/
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e5 + 1;
vint g[N];

const int M = 20;
int kthAncestor[N][M];

void calcAncestor(int cur, int par) {
    kthAncestor[cur][0] = par;
    int p = par;
    int k = 0;
    while (p != -1) {
        p = kthAncestor[p][k];
        k++;
        kthAncestor[cur][k] = p;
    }

    for (int i : g[cur])
        calcAncestor(i, cur);
}

int minInTree[N];

void calcMin(int cur) {
    minInTree[cur] = cur;
    for (int i : g[cur]) {
        calcMin(i);
        minInTree[cur] = min(minInTree[cur], minInTree[i]);
    }
}

int timCur = 1;
int tim[N];
set<pair<int, int>> nxt;
void calcOrder(int cur) {
    v<pair<int, int>> ord;
    for (int i : g[cur])
        ord.pb({minInTree[i], i});
    sort(ord.begin(), ord.end());

    for (auto i : ord)
        calcOrder(i.second);
    tim[cur] = timCur++;
    nxt.insert({tim[cur], cur});
}

bool hasBall[N];
void run() {
    int n, q;
    read(n, q);
    n++;
    int r = -1;
    rep(i, 1, n) {
        int p;
        get p;
        if (p == 0)
            r = i;
        else
            g[p].pb(i);
    }

    rep(i, 1, n)
        rep(j, 0, M)
            kthAncestor[i][j] = -1;
    calcAncestor(r, -1);
    calcMin(r);
    calcOrder(r);

    //for (auto i : nxt) debug(i.first, i.second);
    memset(&hasBall, 0, sizeof(hasBall));
    for (; q; q--) {
        int t;
        get t;
        if (t == 1) {
            int k;
            get k;
            while (k) {
                auto d = *nxt.begin();
                nxt.erase(d);
                hasBall[d.second] = 1;
                k--;
                if (k == 0)
                    put d.second;
            }
        } else {
            int v;
            get v;
            int cur = v;
            int d = 0;
            for (int i = M - 1; i >= 0;) {
                if (!hasBall[kthAncestor[cur][i]])
                    i--;
                else {
                    cur = kthAncestor[cur][i];
                    d += (1 << i);
                }
            }
            hasBall[cur] = 0;
            nxt.insert({tim[cur], cur});

            put d;
        }

        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
