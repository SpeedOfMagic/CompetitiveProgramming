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
int cost(int ha, int ma, int hb, int mb) {
    return min(abs(ha - hb), 24 - abs(ha - hb)) + min(abs(ma - mb), 60 - abs(ma - mb));
}

void run() {
    str a, b;
    read(a, b);

    int ha = (a[0] - '0') * 10 + a[1] - '0';
    int ma = (a[3] - '0') * 10 + a[4] - '0';
    int hb = (b[0] - '0') * 10 + b[1] - '0';
    int mb = (b[3] - '0') * 10 + b[4] - '0';

    int n;
    get n;

    if (n == 0) {put 0; return;}

    int dp[n][24][60]; //dp[i][j][k] - i-е время; j:k на часах, которые != требуемому времени; мин. кол-во кликов
    rep(i, 0, n)
        rep(j, 0, 24)
            rep(k, 0, 60)
                dp[i][j][k] = inf;

    int prH = -1, prM = -1;

    rep(i, 0, n) {
        str s;
        get s;

        int h = (s[0] - '0') * 10 + s[1] - '0';
        int m = (s[3] - '0') * 10 + s[4] - '0';

        //debug(ha, ma, hb, mb, h, m);

        if (i) {
            rep(j, 0, 24)
                rep(k, 0, 60) {
                    dp[i][j][k] = min(dp[i][j][k], dp[i - 1][j][k] + cost(prH, prM, h, m));
                    dp[i][prH][prM] = min(dp[i][prH][prM], dp[i - 1][j][k] + cost(j, k, h, m));
                }
        } else {
            dp[i][hb][mb] = cost(h, m, ha, ma);
            dp[i][ha][ma] = cost(h, m, hb, mb);
        }

        prH = h;
        prM = m;
    }

    int ans = inf;
    rep(j, 0, 24)
        rep(k, 0, 60)
            ans = min(ans, dp[n - 1][j][k]);
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
