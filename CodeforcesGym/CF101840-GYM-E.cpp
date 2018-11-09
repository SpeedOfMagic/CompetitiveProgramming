/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
// Static centroid decomposition + sieve + ability to check if number <= 1e5 has = 2 divisors or more
#include <bits/stdc++.h>
//#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
template<typename T> using v = vector<T>;
//template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
typedef long long longlong;
#define int longlong
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define all(a) (a).begin(), (a).end()
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
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 1e5 + 1;
v<pair<int, int>> t[N];
bitset<N> added;
int prime[N];

int cnt[N];
int version[N];
int onlyDoubles = 0, onlyPrimes = 0;
int curVersion = 0;
int ans = 0;
inline void check(int x) {
    if (version[x] != curVersion) {
        version[x] = curVersion;
        cnt[x] = 0;
    }
}

int siz[N];
int calcSize(int cur, int p = -1) {
    siz[cur] = 1;
    for (pair<int, int> i : t[cur])
        if (!added.test(i.fs) && i.fs != p)
            siz[cur] += calcSize(i.fs, cur);
    return siz[cur];
}

void dfs(int cur, int p, int dist, int type) {
    if (dist < N)
        check(dist);
    check(1);
    if (type == 0)
        ans += onlyDoubles;
    else if (type == 1)
        ans += onlyPrimes - cnt[dist];
    else if (type == 2)
        ans += cnt[1] + 1;
    else
        return;

    for (pair<int, int> i : t[cur])
        if (!added.test(i.fs) && i.fs != p) {
            if (i.sc == 1)
                dfs(i.fs, cur, i.sc * dist, type);
            else if (dist == 1)
                dfs(i.fs, cur, i.sc * dist, prime[i.sc]);
            else if (dist != i.sc && dist < N && prime[dist] == 1 && prime[i.sc] == 1)
                dfs(i.fs, cur, i.sc * dist, 2);
        }

    if (dist < N)
        cnt[dist]++;
    if (type == 1)
        onlyPrimes++;
    else if (type == 2)
        onlyDoubles++;
}

void make_centroid(int cur) {
    curVersion++;
    onlyDoubles = onlyPrimes = 0;
    int lim = calcSize(cur) / 2;
    int pr = -1;
    for (bool again = 1; again;) {
        again = 0;
        for (pair<int, int> i : t[cur])
            if (!added.test(i.fs) && pr != i.fs && siz[i.fs] > lim) {
                pr = cur;
                cur = i.fs;
                again = 1;
                break;
            }
    }

    added.set(cur);
    for (pair<int, int> i : t[cur])
        if (!added.test(i.fs))
            dfs(i.fs, cur, i.sc, prime[i.sc]);
    for (pair<int, int> i : t[cur])
        if (!added.test(i.fs))
            make_centroid(i.fs);
}

inline void run() {
    freopen("evaluations.in", "r", stdin);
    prime[1] = 0;
    for (int i = 2; i < N; i++)
        prime[i] = 1;
    for (int i = 2; i < N; i += 2 - (i == 2))
        if (prime[i] == 1)
            for (int j = i + i; j < N; j += i)
                prime[j] = 3;
    for (int i = 2; i < N; i++)
        if (prime[i] == 1)
            for (int j = 2; i * j < N; j++)
                if (i != j && prime[j] == 1)
                    prime[i * j] = 2;

    memset(version, -1, sizeof version);

    int T;
    get T;
    for (int test = 1; test <= T; test++) {
        rep(i, 1, N) {
            t[i].clear();
            added.reset(i);
        }
        ans = 0;
        int n;
        get n;
        rep(i, 1, n) {
            int v, u, w;
            read(v, u, w);
            t[v].pb({u, w});
            t[u].pb({v, w});
        }
        make_centroid(1);
        put "Case " << test << ": " << ans;
        eol;
    }
}

signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(15); run(); return 0;}
