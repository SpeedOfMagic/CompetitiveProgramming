/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. Notice that subset of tools is correct if and only if one of tools has a[i] = 1, and another one has b[i] = n.
   Also, this subset always has ending tool. So, I want to go through all possible tools
   and find minimum cost of possible subset that ends with that tool.
2. For that I can divide subset into 2 parts: 1st one makes way from column 1 to final tool,
   and second one makes way from column n to final tool.
   Notice that if any tool is included in both subsets, then this subset is not optimal one,
   since I can remove all tools after tool that is included in both subsets.
3. Both parts can be calculated by using dp:
   Let dp[i] mean "Minimum cost of part of subset that ends with tool i".
   If tool hits corresponding border (a[i] = 1 if I solve 1st part or b[i] = n if I solve 2nd), then dp[i] = d[i].
   In any other case, dp[i] is minimum from other dps, whose c[j] is in [a[i]; b[i]] segment.
4. Then, answer is minimum(dp[1st part][i] + dp[2nd part][i] - d[i]) for i in [0; m].
Solution works in O(m ^ 2).
5. To optimize it, I can store values for all possible c[j]'s in corresponding place in the array.
6. So, I need to process 2 queries: Find minimum in segment [a[i]; b[i]], and update value in c[i].
	Both of them can be done with segment tree.
Solution works in O(m * log n + n).
7. To optimize it, I can notice that the only positions I update are c[i]. So, I can reduce n,
if I'll mark c[i] as other numbers, and change a[j] to nearest c[i] >= a[j], and b[j] to nearest c[i] <= b[j].
Since there are maximum of m unique c[i], then n reduces to m.
Solution works in O(m * log m).
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
vint segTree;
int tot;
void init(int n) {
    tot = n;
    while (tot & (tot - 1))
        tot++;
    segTree = vint(2 * tot);
    rep(i, 1, tot * 2)
        segTree[i] = inf;
}

int query(int l, int r, int cur = 1, int ll = 1, int rr = tot) {
    if (l > r)
        return inf;
    if (l == ll && r == rr)
        return segTree[cur];
    int p = (ll + rr) / 2;
    return min(query(l, min(r, p), cur * 2, ll, p), query(max(l, p + 1), r, cur * 2 + 1, p + 1, rr));
}

void update(int pos, int val, int cur = 1, int ll = 1, int rr = tot) {
    if (ll == rr) {
        segTree[cur] = min(segTree[cur], val);
        return;
    }

    int p = (ll + rr) / 2;
    if (pos <= p)
        update(pos, val, cur * 2, ll, p);
    else
        update(pos, val, cur * 2 + 1, p + 1, rr);

    segTree[cur] = min(segTree[cur * 2], segTree[cur * 2 + 1]);
}

void run() {
    int m, n;
    read(m, n);
    int a[m], b[m], c[m], d[m];
    set<int> all;

    bool first[m], last[m];
    rep(i, 0, m) {
        read(a[i], b[i], c[i], d[i]);
        first[i] = (a[i] == 1);
        last[i] = (b[i] == n);
        all.insert(c[i]);
    }
    map<int, int> hsh;
    int p = 1;
    for (int i : all)
        hsh[i] = p++;

    n = -inf;
    rep(i, 0, m) {
        a[i] = (*hsh.lower_bound(a[i])).second;
        auto dd = hsh.upper_bound(b[i]);
        dd--;
        b[i] = (*dd).second;
        c[i] = hsh[c[i]];
        n = max(n, b[i]);
    }

    int dp[2][m];
    rep(k, 0, 2) {
        init(n);
        rep(i, 0, m) {
            if ((!k && first[i]) || (k && last[i]))
                dp[k][i] = d[i];
            else
                dp[k][i] = min(inf, query(a[i], b[i]) + d[i]);
            update(c[i], dp[k][i]);
        }
    }

    //rep(i, 0, 2) { rep(j, 0, m) print(dp[i][j]); eol; }

    int ans = inf;
    rep(i, 0, m)
        ans = min(ans, dp[0][i] + dp[1][i] - d[i]);
    if (ans == inf)
        put -1;
    else
        put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
