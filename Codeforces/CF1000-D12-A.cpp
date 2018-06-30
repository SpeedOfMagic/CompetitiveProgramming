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
    int ss[]={0,0,0,0},m=0,l[]={0,0,0,0};
    rep(i,0,n){
        str s;get s;
        if(s.back()=='M')
            m++;
        else if (s.back()=='S')
            ss[sz(s)-1]++;
        else {
            l[sz(s)-1]++;
        }
    }
    rep(i,0,n){
        str s;get s;
        if(s.back()=='M')
            m--;
        else if (s.back()=='S')
            ss[sz(s)-1]--;
        else {
            l[sz(s)-1]--;
        }
    }
    int ans=0;
    rep(i,0,4){
        ss[i]=max(ss[i],0ll);
        l[i]=max(l[i],0ll);
    }
    m=max(m,0ll);
    //debug(ss[0],ss[1],ss[2],ss[3],m,l[0],l[1],l[2],l[3]);
    rep(i,0,4)ans+=(ss[i]+l[i]);
    ans+=m;put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}