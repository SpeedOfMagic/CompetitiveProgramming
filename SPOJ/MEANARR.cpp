/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution:
1. Number of subarrays in array a1, a2, ... , an with mean >= k is
number of subarrays in array a1 - k, a2 - k, ..., an - k with mean >= 0
2. We want to keep after each iteration i sums of subarrays [0; i], [1; i], ..., [i; i]
3. To make them we need to add sum to all elements, insert new subarray and then find amount of elements > 0
4. All of this can be done with treap, where all elements are sorted, and lazy propagation.
Complexity: O(n log n).
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
const long double EPS = 1e-10;
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//code starts here
struct treap {
    treap *l = nullptr, *r = nullptr;
    int x, y, siz = 1;
    int lazy = 0;
    treap(int xx) : x(xx), y(rng()) {}
    void upd() {
        pushdown();
        siz = ((l == nullptr) ? 0 : l -> siz) + ((r == nullptr) ? 0 : r -> siz) + 1;
    }
 
    void pushdown() {
        x += lazy;
        if (l != nullptr) l -> lazy += lazy;
        if (r != nullptr) r -> lazy += lazy;
        lazy = 0;
    }
};
 
int siz(treap* a) { return (a == nullptr) ? 0 : a -> siz; }
 
treap* merge(treap* t1, treap* t2) {
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
    t1 -> pushdown();
    t2 -> pushdown();
    if (t1 -> y > t2 -> y) {
        t1 -> r = merge(t1 -> r, t2);
        t1 -> upd();
        return t1;
    } else {
        t2 -> l = merge(t1, t2 -> l);
        t2 -> upd();
        return t2;
    }
}
 
pair<treap*, treap*> split(treap* t, int k) {
    if (t == nullptr)
        return {nullptr, nullptr};
    t -> pushdown();
 
    if (siz(t -> l) >= k) {
        pair<treap*, treap*> res = split(t -> l, k);
        t -> l = res.sc;
        t -> upd();
        return {res.fs, t};
    } else {
        pair<treap*, treap*> res = split(t -> r, k - siz(t -> l) - 1);
        t -> r = res.fs;
        t -> upd();
        return {t, res.sc};
    }
}
 
treap *root = nullptr;
 
inline void addAll(int a) {
    if (root != nullptr)
        root -> lazy += a;
}
 
int ans = 0;
inline void calcNotLessThan0() {
    treap *cur = root;
    while (cur != nullptr) {
        cur -> pushdown();
        if (cur -> x >= 0) {
            ans += siz(cur -> r) + 1;
            cur = cur -> l;
        } else
            cur = cur -> r;
    }
}
 
inline void ins() {
    treap *cur = root;
    int amount = 0;
    while (cur != nullptr) {
        cur -> pushdown();
        if (cur -> x < 0) {
            amount += siz(cur -> l) + 1;
            cur = cur -> r;
        } else
            cur = cur -> l;
    }
 
    treap *toIns = new treap(0);
    pair<treap*, treap*> p = split(root, amount);
 
    root = merge(merge(p.fs, toIns), p.sc);
}
 
void prnt(treap* cur) {
    if (cur == nullptr)
        return;
    cur -> pushdown();
    prnt(cur -> l);
    print(cur -> x);
    prnt(cur -> r);
}
 
void run() {
    int n, k;
    read(n, k);
    int a[n];
    rep(i, 0, n) {
        get a[i];
        a[i] -= k;
    }
 
    rep(i, 0, n) {
        ins();
        addAll(a[i]);
        //prnt(root); eol;
        calcNotLessThan0();
    }
 
    put ans;
}
signed main() {ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
 