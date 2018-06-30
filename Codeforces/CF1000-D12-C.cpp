/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
    int n;get n;
    int l[n],r[n];rep(i,0,n)read(l[i],r[i]);sort(l,l+n);sort(r,r+n);rep(i,0,n)r[i]++;
    int p1=0,p2=0;
    int d=0;
    int pr=l[p1];
    int k[n+1];rep(i,0,n+1)k[i]=0;
    for(int t=l[p1];p2<n;t=min((p1<n?l[p1]:inf),r[p2])){
        k[d]+=t-pr-1;

        while(p1<n&&t==l[p1]){
            d++;
            p1++;
        }

        while(p2<n&&t==r[p2]){
            d--;
            p2++;
        }
        k[d]++;
        pr=t;
    }
    rep(i,1,n+1)print(k[i]);
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}