/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
Find and print such string S of maximum length, containing first k letters of alphabet such that,
for every i in [0; |S| - 1], for every j (j != i) in [0; |S| - 1] such S[i]S[i+1] != S[j]S[j+1].

Solution is hard to describe, but code is easy to understand.
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
const long long inf = 4611686018427387903; //2^62 - 1
#if 1  //FileIO
const string fileName = "string";
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
    k += 'a';
    for (char i = 'a'; i < k; i++) {
        put i;
        put i;
        for (char j = k - 1; j > i + 1; j--)
            put j << i;
    }
    for (char i = k - 2; i >= 'a'; i--)
        put i;
    //aaeadacabbebdbccecdedcba
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}