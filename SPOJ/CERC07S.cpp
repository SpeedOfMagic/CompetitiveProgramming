/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution:
Simply do what it says. To effectively reverse subarray you need to use treap.
To find element with minimum index and minimum value use treap like a segment tree.
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
    int val, ind, valind;
    treap(int xx, int iind) : x(xx), y(rng()), val(xx), ind(iind), valind(ind) {}
	int lazy = 0;

    void upd() {
        pushdown();
        val = x;
        valind = ind;
        if (l != nullptr && (l -> val < val || (l -> val == val && l -> valind < valind))) {
            val = l -> val;
            valind = l -> valind;
        }
        if (r != nullptr && (r -> val < val || (r -> val == val && r -> valind < valind))) {
            val = r -> val;
            valind = r -> valind;
        }
        siz = ((l == nullptr) ? 0 : l -> siz) + ((r == nullptr) ? 0 : r -> siz) + 1;
    }

    void pushdown() {
        if (lazy)
            swap(l, r);
        if (l != nullptr) l -> lazy ^= lazy;
        if (r != nullptr) r -> lazy ^= lazy;
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
    cur -> pushdown();
    prnt(cur -> l);
    print(cur -> x);
    prnt(cur -> r);
}

void run() {
    while (1) {
        int n;
        get n;
        if (n == 0)
            break;

        rep(i, 0, n) {
            int a;
            get a;
            root = merge(root, new treap(a, i));
        }

        rep(i, 0, n) {
            treap *cur = root;
			int toCut = 0;
            while (1) {
                cur -> pushdown();
				if (cur -> l != nullptr && cur -> l -> valind == cur -> valind)
					cur = cur -> l;
				else if (cur -> r != nullptr && cur -> r -> valind == cur -> valind) {
					toCut += siz(cur -> l) + 1;
					cur = cur -> r;
				} else {
				    toCut += siz(cur -> l);
					assert(cur -> ind == cur -> valind);
					break;
				}
            }

			print(toCut + 1 + i);
			auto p = split(root, toCut);
			auto pp = split(p.sc, 1);

			if (p.fs != nullptr)
                p.fs -> lazy = 1;
			root = merge(p.fs, pp.sc);
            //prnt(root); eol;
        }

		put "\n";
    }
}
signed main() {ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
