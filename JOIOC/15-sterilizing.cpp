/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/* Solution:
1. Obviously it can be solved by lazy segment tree.
2. Each node keeps 2 elements: lazy (how much time I need to spray) and queue,
where future values after each spray are stored.
3. For each spray, I just pop element from queue and process this like a normal lazy segment tree.
4. If I need to update element on position, I just rewrite all queues on path from root to position.
5. If k = 1, then I ignore second query and limit queue size to log(MAX_A) = 30.

Time complexity: O(n + q * log(MAX_N) * log(MAX_A)). Memory: O(n * log(MAX_A)).
*/
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
//#define int long long
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
void println(){eol;} template<typename Arg,typename... Args> void println(Arg  arg,Args...  args){put (arg)<<" ";println(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 131072;
const int LIM = 30;
queue<long long> segTree[N * 2];
int lazy[N * 2];
int k;
 
inline long long front(queue<long long>& cur) { return (cur.empty() ? 0ll : cur.front()); }
 
inline void processLazy(int cur) {
    if (cur < N) {
        lazy[cur * 2] += lazy[cur];
        lazy[cur * 2 + 1] += lazy[cur];
    }
 
    for (; lazy[cur] && !segTree[cur].empty(); lazy[cur]--)
        segTree[cur].pop();
 
    lazy[cur] = 0;
}
 
inline void updateElement(int cur) {
    queue<long long> left = segTree[cur * 2], right = segTree[cur * 2 + 1];
    if (sz(left) < sz(right))
        swap(left, right);
 
    while (!segTree[cur].empty())
        segTree[cur].pop();
 
    while (!left.empty()) {
        segTree[cur].push(front(left) + front(right));
        left.pop();
        if (!right.empty())
            right.pop();
    }
}
 
 
inline void updatePos(int p, long long val, int cur = 1, int ll = 1, int rr = N) {
    processLazy(cur);
    if (ll != rr) {
        int mid = (ll + rr) / 2;
        if (p <= mid) {
            updatePos(p, val, cur * 2, ll, mid);
            processLazy(cur * 2 + 1);
        } else {
            processLazy(cur * 2);
            updatePos(p, val, cur * 2 + 1, mid + 1, rr);
        }
 
        updateElement(cur);
    } else {
        while (!segTree[cur].empty())
            segTree[cur].pop();
 
        for (; val && sz(segTree[cur]) < LIM; val /= k)
            segTree[cur].push(val);
    }
}
 
inline void spray(int l, int r, int cur = 1, int ll = 1, int rr = N) {
    if (k == 1)
        return;
    //debug(l, r, cur, ll, rr);
    if (l == ll && r == rr) 
        lazy[cur]++;
    
 
    processLazy(cur);
    if (l > r || (l == ll && r == rr))
        return;
 
    int mid = (ll + rr) / 2;
    spray(l, min(r, mid), cur * 2, ll, mid);
    spray(max(l, mid + 1), r, cur * 2 + 1, mid + 1, rr);
    updateElement(cur);
}
 
inline long long query(int l, int r, int cur = 1, int ll = 1, int rr = N) {
    processLazy(cur);
    if (l > r)
        return 0;
    if (l == ll && r == rr)
        return front(segTree[cur]);
    int mid = (ll + rr) / 2;
    return query(l, min(r, mid), cur * 2, ll, mid) + query(max(l, mid + 1), r, cur * 2 + 1, mid + 1, rr);
}
 
void run() {
    int n, q;
    read(n, q, k);
 
    rep(i, 0, n)
        updatePos(i + 1, getInt());

  	rep(i, 0, 2 * N)
      	lazy[i] = 0;

    for (; q; q--) {
        int s, t, u;
        read(s, t, u);
        if (s == 1)
            updatePos(t, u);
        else if (s == 2)
            spray(t, u);
        else
            put query(t, u), eol;
    }
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}