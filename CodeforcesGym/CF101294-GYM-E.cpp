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
const string fileName = "gagarincup";
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
str s;
double ans = 0;
str itostr(int a){
    str r="";
    if(a==0)r="0";
    while(a){
        r+=char('0'+a%10);
        a/=10;
    }
    return r;
}
double a1,b1,a2,b2;
void bt(double p, int curMatch, int aScore, int bScore) {
    //debug(curMatch, aScore, bScore);
    if (aScore == 4 || bScore == 4) {
        str d = itostr(aScore);
        d+="-";
        d+=itostr(bScore);
        if(d==s)
            ans+=p;
        return;
    }
    if(curMatch<3||curMatch==5||curMatch==7){//1 площадка
        bt(p * a1, curMatch + 1, aScore + 1, bScore);
        bt(p * b1, curMatch + 1, aScore, bScore + 1);
    } else {
        bt(p * a2, curMatch + 1, aScore + 1, bScore);
        bt(p * b2, curMatch + 1, aScore, bScore + 1);
    }
}

void run() {
    read(a1,b1,a2,b2);
    get s;
    bt(1, 1, 0, 0);
    put ans;
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}