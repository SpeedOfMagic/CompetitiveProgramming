/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
A connected graph with n vertices and m edges is given. 2 players play the game:
On each turn, player removes 1 edge from graph.
If graph becomes not connected, then that player loses.
Determine the winner, or find out if it's a draw.

It's needed to prove that when playing this game, the result is always tree.
Then, the winning player depends on amount of turns.
Also, if m = 0, then there is a draw, since nobody removes roads.
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
const string fileName = "graphgame";
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
    int t = n - 1;
    if (m == 0)
        put "Draw";
    else if ((m - t) % 2 == 0)
        put "Alice";
    else
        put "Bob";
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}