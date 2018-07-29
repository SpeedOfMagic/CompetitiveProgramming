/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/53567
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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
struct segTree {
    int val;
    segTree *left = nullptr, *right = nullptr;
    segTree(int v):val(v) {}
};

int n;

v<segTree*> version = {nullptr};

int query(int l, int r, segTree *cur, int ll = 0, int rr = n - 1) {
    if (cur == nullptr || l > r)
        return 0;
    if (l == ll && r == rr)
        return cur -> val;
    int mid = (ll + rr) / 2;
    return query(l, min(r, mid), cur -> left, ll, mid) + query(max(l, mid + 1), r, cur -> right, mid + 1, rr);
}

int query(int p, segTree *cur, int ll = 0, int rr = n - 1) {
    if (ll == rr)
        return cur -> val;
    int mid = (ll + rr) / 2;
    if (p <= mid)
        return query(p, cur -> left, ll, mid);
    else
        return query(p, cur -> right, mid + 1, rr);
}

int value(segTree* cur) {
    if (cur == nullptr)
        return 0;
    return cur -> val;
}

segTree* left(segTree* cur) {
    if (cur == nullptr)
        return nullptr;
    return cur -> left;
}

segTree* right(segTree* cur) {
    if (cur == nullptr)
        return nullptr;
    return cur -> right;
}

void update(int num, int val) {
    segTree* parallel = version.back();
    version.pb(new segTree(value(parallel) + val));
    segTree* cur = version.back();

    int ll = 0, rr = n - 1;
    while (ll != rr) {
        int mid = (ll + rr) / 2;
        if (num > mid) {
            ll = mid + 1;
            cur -> left = left(parallel);
            parallel = right(parallel);
            cur -> right = new segTree(value(parallel) + val);
            cur = cur -> right;
        } else {
            rr = mid;
            cur -> right = right(parallel);
            parallel = left(parallel);
            cur -> left = new segTree(value(parallel) + val);
            cur = cur -> left;
        }
    }
}
const int N = 35000;
const int K = 50;
int rVersion[N];
int dp[N][K];

int arr[N];


int cost(int l, int r) {
    return query(l, r, version[rVersion[r]]);
}

int range[N];

int solve(int i, int j, int l, int r) {
    int p = 0;
    int res = 0;
    int curCost = cost(min(i - 1, r) + 1, i);
    for (int k = min(i - 1, r); k >= l; k--) {
        int pos = dp[k][j - 1] + curCost;
        if (res < pos) {
            res = pos;
            p = k;
        }

        if (range[k] >= i)
            curCost++;
    }

    dp[i][j] = res;
    return p;
}

void calc(int j, int a, int b, int x, int y) {
    if (a > b)
        return;
    int z = (a + b) / 2;
    int p = solve(z, j, x, y);

    calc(j, a, z - 1, x, p);
    calc(j, z + 1, b, p, y);
}

void run() {
    int k;
    read(n, k);
    int prev[n];
    rep(i, 0, n)
        prev[i] = -1;

    rep(i, 0, n)
        range[i] = inf;

    rep(i, 0, n) {
        arr[i] = getInt() - 1;
        if (prev[arr[i]] != -1) {
            update(prev[arr[i]], -1);
            range[prev[arr[i]]] = i - 1;
        }

        prev[arr[i]] = i;
        update(i, 1);

        rVersion[i] = sz(version) - 1;
    }

    rep(i, 0, n)
        dp[i][0] = query(0, i, version[rVersion[i]]);

    rep(j, 1, k)
        calc(j, 0, n - 1, 0, n - 1);
    put dp[n - 1][k - 1];
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
