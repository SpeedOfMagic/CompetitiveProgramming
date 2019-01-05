/** MIT License Copyright (c) 2018-2019(!) Vasilyev Daniil **/
/*
Statement:
There is a train which has k seats and goes from station 1 to 2 to ... to n.
Also, there are m people, which have values l r x. It means that each of them
bought ticket from station l to station r and occupied seat x.
You can also buy tickets, just like those m people did.
You need to process q queries, each has values l r and asks the minimum number of tickets to ride from station l to station r.
*/
/*
Solution:
Use greedy approach and for each station find maximum station number it's possible to reach.
Then construct functional acyclic graph upon this, and solve queries by using binary lifting (by finding the 1st vertex with number >= r).  
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
typedef long long longlong;
//#define int longlong
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
const string fileName = "trains";
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
//code starts here
const int N = 2e5 + 1;
const int logN = 18;
int toAdd[N];
v<pair<int, int>> occupied[N];
int opt[N];
int lim[N];
int f[N][logN];

void run() {
    memset(toAdd, -1, sizeof toAdd);

    int n, m, k;
    read(n, m, k);
    for (int i = 0; i < m; i++) {
        int l, r, x;
        read(l, r, x);
        l--; r--; x--;
        occupied[x].pb({l, r});
    }

    rep(i, 0, k) {
        int pr = 0;
        sort(occupied[i].begin(), occupied[i].end());
        for (auto j : occupied[i]) {
            toAdd[pr] = max(toAdd[pr], j.fs);
            pr = j.sc;
        }
        toAdd[pr] = n - 1;
    }

    int mx = -1;
    rep(i, 0, n) {
        mx = max(mx, toAdd[i]);
        opt[i] = (mx <= i) ? -1 : mx;
    }

    rep(j, 0, logN)
        rep(i, 0, n)
            if (j && f[i][j - 1] == -1)
                f[i][j] = -1;
            else
                f[i][j] = j ? f[f[i][j - 1]][j - 1] : opt[i];

    int q;
    get q;
    for (; q; q--) {
        int l, r;
        read(l, r);
        l--; r--;
        int ans = 0;
        for (int i = logN - 1; i >= 0; i--) {
            if (f[l][i] != -1 && f[l][i] < r) {
                l = f[l][i];
                ans += (1 << i);
            }
        }

        if (l == r)
            put 0;
        else if (f[l][0] >= r)
            put ans + 1;
        else
            put -1;
        eol;
    }
}
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run(); return 0;}
