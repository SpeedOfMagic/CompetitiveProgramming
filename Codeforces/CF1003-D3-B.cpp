/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
// Editorial: https://codeforces.com/blog/entry/60417
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
    int a, b, x;
    read(a, b, x);

    bool sw = 0;
    if (a > b) {
        swap(a, b);
        sw = 1;
    }

    str ans = "";
    if (sw)
        ans += "0";
    else
        ans += "1";

    b--;

    while(x) {
        if (ans.back() == '0') {
            ans += "1";
            if (sw)
                a--;
            else
                b--;
        } else {
            ans += "0";

            if (sw)
                b--;
            else
                a--;
        }

        x--;
    }

    if (sw)
        swap(a, b);

    for (char i : ans) {
        while (i == '0' && a) {
            put "0";
            a--;
        }

        while (i == '1' && b) {
            put "1";
            b--;
        }

        put i;
    }
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}