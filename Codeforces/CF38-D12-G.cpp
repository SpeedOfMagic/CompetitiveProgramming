/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution: 
To find where i-th person will stand you can use binary search + finding maximum on a prefix.
Then insert that person into position where it will stand. All of it can be done with a treap.
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
typedef long long ll;
//#define int ll
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
const long double EPS = 1e-12;
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
    int val, ind;
    treap(int xx, int iind) : x(xx), y(rng()), val(xx), ind(iind) {}
    void upd() {
        val = x;
        if (l != nullptr) { val = max(val, l -> val); }
        if (r != nullptr) { val = max(val, r -> val); }
        siz = ((l == nullptr) ? 0 : l -> siz) + ((r == nullptr) ? 0 : r -> siz) + 1;
    }
};

int siz(treap* a) { return (a == nullptr) ? 0 : a -> siz; }

treap* merge(treap* t1, treap* t2) {
    if (t1 == nullptr)
        return t2;
    if (t2 == nullptr)
        return t1;
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

inline int query(int amount) {
    int ans = 0;
    treap *cur = root;
    while (cur != nullptr) {
        if (siz(cur -> l) + 1 <= amount) {
            ans = max(ans, max((cur -> l == nullptr) ? 0 : cur -> l -> val, cur -> x));
			amount -= siz(cur -> l) + 1;
            cur = cur -> r;
        } else
            cur = cur -> l;
    }
    return ans;
}

void prnt(treap* cur) {
    if (cur == nullptr)
        return;
    prnt(cur -> r);
    print(cur -> ind + 1);
    prnt(cur -> l);
}

void run() {
    int n;
    get n;
    rep(i, 0, n) {
        int a, c;
        read(a, c);
        int l = 0, r = min(c, i);
        while (l < r) {
            int mid = (l + r + 1) >> 1;
            if (query(mid) > a)
                r = mid - 1;
            else
                l = mid;
        }

        auto t = split(root, l);
        root = merge(merge(t.fs, new treap(a, i)), t.sc);
    }

    prnt(root);
}
signed main() {ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}