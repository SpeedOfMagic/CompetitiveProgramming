/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
Fibonacci strings work like this:
Fib[0] = "a";
Fib[1] = "b";
Fib[i] = Fib[1] + Fib[0].
A number k is given (0 <= k <= 80). Find size of the largest subpalindrome of Fib[k].

I don't know why, but starting from 5, size of the largest subpalindrome of Fib[k]
is Fib[k].length() - 2. So, I just pushed the values of first 5 possible variants into array,
and others calculated just like usual fibonacci numbers.
*/
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
const string fileName = "fibstring";
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
    int k;get k;
    int d[]={1,1,1,3,4};
    if(k<5)put d[k];
    else{
        int ppr=1,pr=1;
        rep(i,2,k+1){
            int c=ppr+pr;
            ppr=pr;pr=c;
        }
        put pr-2;
    }
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}