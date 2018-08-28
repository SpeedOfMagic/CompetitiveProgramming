/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
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
const int N = 131072;
int a[N], b[N], ab[N];
vint indA[N], indB[N], indAB[N];
int _rank(int num, int r, int x) {
    if (num == 1)
        return (upper_bound(indA[x].begin(), indA[x].end(), r) - indA[x].begin());
    else if (num == 2)
        return (upper_bound(indB[x].begin(), indB[x].end(), r) - indB[x].begin());
    else
        return (upper_bound(indAB[x].begin(), indAB[x].end(), r) - indAB[x].begin());
}

bool hasNon(int ind, int l, int r) {
    return (r - l + 1) !=
        (_rank(1, r, a[ind]) -  _rank(1, l - 1, a[ind])) +
        (_rank(2, r, b[ind]) -  _rank(2, l - 1, b[ind])) -
        (_rank(3, r, ab[ind]) - _rank(3, l - 1, ab[ind]));
}

int closest[N];

int segTree[2 * N];

void init() {
    rep(i, 0, N)
        segTree[i + N] = i;
    for (int i = N - 1; i; i--)
        if (closest[segTree[i * 2 + 1]] > closest[segTree[i * 2]])
            segTree[i] = segTree[i * 2 + 1];
        else
            segTree[i] = segTree[i * 2];
}

int query(int l, int r, int cur = 1, int ll = 1, int rr = N) {
    if (l > r)
        return -1;
    if (l == ll && r == rr)
        return segTree[cur];
    int mid = (ll + rr) / 2;
    int aa = query(l, min(r, mid), cur * 2, ll, mid), bb = query(max(l, mid + 1), r, cur * 2 + 1, mid + 1, rr);
    if (bb != -1 && (aa == -1 || closest[aa] < closest[bb]))
        return bb;
    else
        return aa;
}

void run() {
    int n;
    get n;
    rep(i, 0, n) {
        a[i] = 1;b[i] = 1;
        read(a[i], b[i]);
        ab[i] = a[i] * (1e9 + 1) + b[i];
    }

    rep(i, 0, N)
        closest[i] = -1;

    rep(z, 0, 3) {
        map<int, int> hsh;
        int p = 0;
        auto point = a;
        if (z == 1)
            point = b;
        else if (z == 2)
            point = ab;
        for (auto cur = point; cur != point + n; cur++) {
            int i = *cur;
            if (!hsh.count(i))
                hsh[i] = p++;
            *cur = hsh[i];
        }
    }

    rep(i, 0, n) {
        indA[a[i]].pb(i);
        indB[b[i]].pb(i);
        indAB[ab[i]].pb(i);
    }

    rep(i, 0, n) {
        int l = 0, r = i - 1;
        while (l < r) {
            int mid = (l + r) / 2;
            int ll = mid + 1, rr = r;
            if (hasNon(i, ll, rr))
                l = ll;
            else
                r = mid;
        }
        //debug(l, r);
        if (a[l] != a[i] && b[l] != b[i])
            closest[i] = l;
    }

    //rep(i, 0, n) debug(closest[i]);

    init();

    int k;
    get k;
    for (; k; k--) {
        int l, r;
        read(l, r);
        int ind = query(l, r);
        //continue;
        if (closest[ind] == -1 || closest[ind] < l - 1)
            put 0 << " " << 0;
        else
            put ind + 1 << " " << closest[ind] + 1;
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
