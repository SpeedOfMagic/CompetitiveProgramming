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

const long long mod2 = 36028797018963913; //2^55-55
const long long base = 26; //alphabet size
const char startingLetter = 'a'; //starting letter of the alphabet

long long hashChar(char c){
    return c - startingLetter + 1;
}

long long hashStr(long long prevHash, char curChar){
    return ((prevHash * 26) % mod2 + hashChar(curChar)) % mod2;
}

long long hashStr(string& s){
    long long res = 0;
    for(char i : s)
        res = hashStr(res, i);
    return res;
}


void run() {
    int n, d, K;
    read(n, d, K);

    if (n == 2 && d == 1) {
        
        put "YES";eol; put "1 2";eol;
        return;
    }
    if (n <= d || K == 1) {
        put "NO";
        return;
    }


    v<pair<int, int>> E;

    rep(i, 1, d + 1) {
        E.pb({i, i + 1});
    }

    int p = d + 2;
    int mxDepth[++n];
    rep(i, 1, n)
        mxDepth[i] = 0;

    for (int i = 2; i <= d + 1 - i + 1; i++) {
        mxDepth[i] = mxDepth[i - 1] + 1;
        mxDepth[d + 1 - i + 1] = mxDepth[i];
    }

    if (p == n) {
        put "YES";
        eol;

        for (pair<int, int> i : E)
            debug(i.first, i.second);

        return;
    }

    rep(k, 1, n) {
        if (mxDepth[k] == 0)
            continue;

        int r = 2 - (k > d + 1);
        while (r < K) {
            E.pb({k, p});

            mxDepth[p] = mxDepth[k] - 1;

            p++;

            if (p == n) {
                put "YES";
                eol;

                for (pair<int, int> i : E)
                    debug(i.first, i.second);

                return;
            }

            r++;
        }
    }

    put "NO";
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}