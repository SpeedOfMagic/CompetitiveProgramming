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

void run() {
    int n,m;read(n,m);
    int a[n+2];rep(i,1,n+1)get a[i];a[n+1]=m;a[0]=0;
    int pre[n+2];pre[0]=0;
    rep(i,1,n+2){
        if((i-1)%2==0){
            pre[i]=pre[i-1]+a[i]-a[i-1];
        } else {
            pre[i]=pre[i-1];
        }
    }

    int sum[n+2];sum[n+1]=0;
    for(int i=n;i>=0;i--){
        if(i%2){
            sum[i]=a[i+1]-a[i]+sum[i+1];
        }else{
            sum[i]=sum[i+1];
        }
    }

    int ans=pre[n+1];
    rep(i,0,n+1){
        if(a[i]+1==a[i+1])continue;
        ans=max(ans, pre[i] + sum[i+1] + a[i+1]-(a[i]+1));
    }
    put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}