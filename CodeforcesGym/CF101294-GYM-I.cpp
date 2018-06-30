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
const int inf = 4611686018427387903; //2^62 - 1
#if 1  //FileIO
const string fileName = "sms";
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
    int n, m;
    read(n, m);

    int a[n];
    rep(i, 0, n)
        get a[i];

    int dp[n][m][n];rep(i,0,n)rep(j,0,m)rep(k,0,n)dp[i][j][k]=1e9;
    dp[0][0][0]=a[0];

    int rf[n][m];

    rep(i,1,n)rep(j,0,m){
        rep(k,1,n)
            dp[i][j][k] = dp[i-1][j][k-1] + a[i] * (k+1);

        if(j) {
            int rfK = 0;
            rep(k,1,n) {
                if(dp[i-1][j-1][rfK]>dp[i-1][j-1][k])
                    rfK=k;
            }
            dp[i][j][0] = dp[i-1][j-1][rfK] + a[i];
            rf[i][j] = rfK;
        }
    }
    int rfJ = 0, rfK = 0;
    rep(j,0,m)rep(k,0,n) {
        if(dp[n-1][j][k] < dp[n-1][rfJ][rfK]) {
            rfJ = j;
            rfK = k;
        }
    }
    vint ans(m, 0);
    for(int i = n - 1; i >= 0; i--) {
        //debug(i, rfJ, rfK);
        ans[rfJ] = rfK + 1;

        while(rfK) {
            i--;
            rfK--;
        }

        rfK = rf[i][rfJ];
        rfJ--;
    }

    for(int i:ans)
        print(i);
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}