/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
// Editorial: https://www.hackerrank.com/contests/ioi-2014-practice-contest-2/challenges/questions-i-ask-myself-ioi14/editorial
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
const int M = 3e5 + 1;
void run() {
    vint erato[M];
    rep(i, 1, M)
        for (int j = 1; i * j < M; j++)
            erato[i * j].pb(i);

    vint numbers[M];

    int q;
    get q;
    for (; q; q--) {
        str query;
        get query;
        if (query == "ADD") {
            int v;
            get v;
            for (int i : erato[v])
                numbers[i].pb(v);
        } else {
            int a, b, m;
            read(a, b, m);
            int l = lower_bound(numbers[m].begin(), numbers[m].end(), a) - numbers[m].begin();
            int r = upper_bound(numbers[m].begin(), numbers[m].end(), b) - numbers[m].begin();
            put r - l;
            eol;
        }
    }
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
