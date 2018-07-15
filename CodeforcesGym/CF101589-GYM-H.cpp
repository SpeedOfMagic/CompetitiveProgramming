/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
#if 1  //FileIO
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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    int n;
    get n;

    int h[n + 2];
    h[0] = 0; h[n + 1] = 0;
    rep(i, 1, n + 1)
        get h[i];

    int P = n * 2;
    rep(i, 1, n + 2)
        P += abs(h[i] - h[i - 1]);
    int p = P / 2 + P % 2;
    int dp[n + 2][P + 1]; //dp[i][j][k]
    int rf[n + 2][P + 1];
    int rfP[n + 2][P + 1];
    rep(i, 0, n + 2)
        rep(j, 0, P + 1) {
            dp[i][j] = 0;
            rf[i][j] = -1;
            rfP[i][j] = -1;
        }

    rep(i, 1, n + 2) {
        int hToGet = 0;
        for (int j = i - 1; j >= 0; j--) {
            int pToRemove = -abs(h[i] - h[j]);
            for (int k = j + 1; k < i; k++) {
                pToRemove += 2;
                pToRemove += abs(h[k - 1] - h[k]);
            }
            pToRemove += abs(h[i] - h[i - 1]);

            for (int k = P; k >= pToRemove; k--)
                if (dp[i][k - pToRemove] < hToGet + dp[j][k]) {
                    dp[i][k - pToRemove] = hToGet + dp[j][k];
                    rf[i][k - pToRemove] = j;
                    rfP[i][k - pToRemove] = k;
                }

            if (j == 0)
                break;

            hToGet += h[j];
        }
    }

    int ans = p;
    rep(i, p, P + 1)
        if (dp[n + 1][i] > dp[n + 1][ans])
            ans = i;

    put dp[n + 1][ans];
    eol;

    vint res;
    int r = n + 1;
    while (rf[r][ans] != -1) {
        int z = rf[r][ans];
        for (int i = z + 1; i < r; i++)
            res.pb(i);
        ans = rfP[r][ans];
        r = z;
    }

    sort(res.begin(), res.end());
    put sz(res);eol;

    for (int i : res)
        print(i);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}