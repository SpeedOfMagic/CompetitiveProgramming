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
v<pair<int, int>> functions;
vint sw;

int findMin(int x) {
    int v = (upper_bound(sw.begin(), sw.end(), x) - sw.begin()) - 1;
    return functions[v].fs * x + functions[v].sc;
}

void add(int k, int m) { //kx + m
    while (!functions.empty() && sw.back() * functions.back().fs + functions.back().sc >= sw.back() * k + m) {
        functions.pop_back();
        sw.pop_back();
    }

    if (functions.empty())
        sw.pb(0);
    else {
        int k1 = functions.back().fs, m1 = functions.back().sc;
        int k2 = k, m2 = m;
        int x = (m2 - m1) / (k1 - k2);
        /*
        k1x + m1 >= k2x + m2
        k1x - k2x >= m2 - m1
        (k1 - k2)x >= m2 - m1
        x >= (m2 - m1) / (k1 - k2)
        
        k1x + m1 >= k2x + m2
        m1 - m2 >= k2x - k1x
        x <= (m1 - m2) / (k2 - k1) | * (-1)
        x >= (m2 - m1) / (k2 - k1)
        */
        //debug(k1, x, m1, k2, m2);
        while (k1 * x + m1 < k2 * x + m2)
            x++;
        sw.pb(x);
    }

    functions.pb({k, m});
}

void run() {
    int n;
    get n;
    int q[n], a[n], b[n], r[n], d[n];
    rep(i, 0, n)
        read(q[i], a[i], b[i], r[i], d[i]);

    int best[n];
    int s = 0;
    for (int i = n - 1; i >= 0; i--) {
        add(-s, r[i]);
        int opt = findMin(d[i]) + s * d[i];
        if (q[i] > opt)
            best[i] = q[i] - opt;
        else
            best[i] = -1;
        s++;
    }

    //debug(sw[0], sw[1]);
    const int mod = 1e9 + 7;
    int ans = 0;
    rep(i, 0, n) {
        if (best[i] == -1)
            continue;
        
        int l = (best[i] - a[i]) / b[i]; //x; a + bx <= best[i]; x <= (best[i] - a) / b
        
        if (l <= 0)
            continue;
        l %= mod;
        best[i] %= mod;
        ans = (ans + (best[i] * l) % mod) % mod;
        int v = ((l * (l + 1ll)) % mod * 500000004ll) % mod;
        assert(v >= 0);
        assert(l > 0);
        assert(l * (l + 1ll) > 0);
        assert(best[i] > 0);
        //debug(l, v);
        //debug(i, l, best[i]);
        ans = ((ans - ((a[i] * l) % mod + (b[i] * v) % mod)) % mod + mod) % mod;
    }
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}