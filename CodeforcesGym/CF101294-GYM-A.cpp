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
const string fileName = "army3";
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
    int n,k;read(n,k);
    int h[n];rep(i,0,n)get h[i];
    int b[n];rep(i,0,n)b[i]=h[i];
    sort(b,b+n);
    map<int,int>d;

    rep(l,0,n){
        int r=l;
        while(r<n&&b[r]==b[l])r++;
        r--;
        d[b[l]]=l;
        l=r;
    }
    int pok[n];rep(i,0,n)pok[i]=d[h[i]];
    int pr[n];pr[0]=pok[0];rep(i,1,n)pr[i]=pr[i-1]+pok[i];
    int l=0;
    int ans=0, mx=0;
    rep(r,k-1,n){
        int val=pr[r] - pr[l] + pok[l];
        if(val>mx){
            mx=val;
            ans=l;
        }
        l++;
    }
    put ans+1;
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}