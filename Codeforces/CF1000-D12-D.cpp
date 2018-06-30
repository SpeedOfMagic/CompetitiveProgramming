/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60288
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const int inf = 4611686018427387903; //2^62 - 1
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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int mod = 998244353;

int pow(int a, int b) {
    if (b == 0)
        return 1 % mod;

    if (b == 1)
        return a % mod;

    int res = pow(a, b/2);
    res = (res * res) % mod;

    if (b % 2 == 1)
        return (a * res) % mod;

    return res;
}

//uses pow
int inv(int a) {
    int b = mod - 2;
    return pow(a, b);
}
vector<int> factorials = {1};
void initFactorials(unsigned int n) { //calculates [1! % mod, 2! % mod, ... , n! % mod]
    for (unsigned int i = factorials.size(); i <= n; i++) {
        int d = factorials.back();
        factorials.push_back((d * i) % mod);
    }
}

//uses initFactorials, inv;
int c(int k, int n){
    initFactorials(n);
    return ((factorials[n] * inv(factorials[k])) % mod * inv(factorials[n - k])) % mod;
}

void run() {
    int n;get n;
    int a[n];rep(i,0,n)get a[i];
    int dp[n];rep(i,0,n)dp[i]=0;//dp[i] - число хороших подпос., заканч. на элементе i
    int s=0;
    rep(i,0,n){
        if(a[i]<=0){s=(s+dp[i])%mod;continue;}
        int k=a[i];
        rep(j,i+k,n){
            int p=c(k-1,j-i-1);
            dp[j]=(dp[j]+((p*(s+1))%mod))%mod;
            //if(j==4)debug(dp[j],i,s);
        }
        s=(s+dp[i])%mod;
    }
/**
1 2 4 5
4 5
1 5
2 5
1 3 4 5
2 3 4 5
**/
    int ans=0;
    rep(i,0,n)ans=(ans+dp[i])%mod;
    //for(int i:dp)print(i);eol;
    put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}