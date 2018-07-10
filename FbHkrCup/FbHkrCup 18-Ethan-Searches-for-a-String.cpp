/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://www.facebook.com/notes/2249775598371662
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
bool ethanCode(str a, str b) {
    int i = 0, j = 0;
    while (1) {
        if (i == sz(a))
            return 1;
        if (j == sz(b))
            return 0;

        if (a[i] == b[j]) {
            i++;
            j++;
        } else if (i == 0)
            j++;
        else
            i = 0;
    }
}

str solve(str a) {
    str k = a;
    str d = "";
    for (char i : a) {
        d += i;
        if (ethanCode(a, d + k) == 0)
            return d + k;
    }

    return "Impossible";
}

void run() {
    int t;
    get t;
    rep(test, 1, t + 1) {
        str a;
        get a;
        put "Case #" << test << ": " << solve(a);
        eol;
    }
}

int32_t main() {srand(time(0)); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
