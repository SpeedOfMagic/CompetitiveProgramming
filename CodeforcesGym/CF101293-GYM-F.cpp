/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
An array of k elements (k <= 5; max value of elements < 2^10) is given.
You may do any amount of turns, in turn #i:
Choose any element j. Then, a[j] = a[j] - (1 << (i - 1)); 
Determine if it's possible to turn all elements into zeros only.

Since max value < 2^10, then there is maximum 10 turns in game.
So, I may go through all possible arrays, and process them like a turn of events, and check if it will work.

Solution works in k ^ log2(max).
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
const string fileName = "monsters";
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
    int k;
    get k;
    int z[k];
    rep(i, 0, k)
        get z[i];

    rep(a, 0, k)rep(b, 0, k)rep(c, 0, k)rep(d, 0, k)rep(e, 0, k)
    rep(f, 0, k)rep(g, 0, k)rep(h, 0, k)rep(i, 0, k)rep(j, 0, k) {
        int x[k];
        rep(l, 0, k)
            x[l] = z[l];

        int dd[11] = {a, b, c, d, e, f, g, h, i, j, 0};
        for (int i = 0; i < 11; i++) {
            int p = 1 << i;
            if (p > x[dd[i]]) {
                bool yes = all_of(x, x + k, [](int a){return a == 0;});
                if (yes) {
                    put "Yes";
                    //for (int i : dd)debug(i);
                    return;
                } else break;
            } else x[dd[i]] -= p;
        }
    }
    put "No";
}
int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}