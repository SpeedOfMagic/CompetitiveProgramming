/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/60511
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

void run() {
    int n, m;
    read(n, m);

    int a[n];
    rep(i, 0, n)
        get a[i];

    int lessM[n], equalM[n], moreM[n];

    lessM[0] = a[0] < m;
    equalM[0] = a[0] == m;
    moreM[0] = a[0] > m;

    rep(i, 1, n) {
        lessM[i] = (a[i] < m) + lessM[i - 1];
        equalM[i] = (a[i] == m) + equalM[i - 1];
        moreM[i] = (a[i] > m) + moreM[i - 1];
    }

    int penalty[n];
    rep(i, 0, n)
        penalty[i] = moreM[i] - lessM[i];

    int ans = 0;
    int nearestM = -1;

    map<int, int> pos;
    pos[0] = 1;

    rep(r, 0, n) {

        if (a[r] == m) {
            rep(i, nearestM + (nearestM == -1), r)
                pos[penalty[i]]++;

            nearestM = r;
        }

        if (nearestM == -1)
            continue;

        /**
        for (int i : pos)
            if (penalty[r] == i || penalty[r] - 1 == i) //penalty[r] - i == 0 || penalty[r] - i == 1
                ans++;
        **/
        ans += pos[penalty[r]] + pos[penalty[r] - 1];

    }

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}