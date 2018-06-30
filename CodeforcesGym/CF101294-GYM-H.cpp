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
const string fileName = "photo";
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
    str s[3];read(s[0],s[1],s[2]);

    rep(i,0,3){
        str d="";d+=s[i][0];d+=s[i][1];
        str k="";k+=s[i][3];k+=s[i][4];
        str t=s[i].substr(6);
        s[i]=t+k+d;
    }
    int ans=0;
    //debug(s[0],s[1],s[2]);
    rep(year,1970,2039)rep(month,1,13)rep(day,1,32){
        bool vis=year%4==0;
        int days[]={-1,31,28+vis,31,30,31,30,31,31,30,31,30,31};
        if(days[month]<day)continue;

        int k[]={year/1000,year%1000/100,year%100/10,year%10,month/10,month%10,day/10,day%10};
        bool z=1;
        rep(i,0,8){
            if(k[i]+'0'==s[0][i]||s[0][i]=='?')z=1;
            else{z=0;break;}
        }
        if(!z)continue;
        str t="";rep(i,0,8)t+=char(k[i]+'0');
        if(s[1]<=t&&t<=s[2])ans++;
    }
    put ans;
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}