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
    int n, q;
    read(n, q);

    int bin[32];
    rep(i, 0, 32)
        bin[i] = 0;

    rep(i, 0, n) {
        int a;
        get a;
        int d = 0;
        while (a >> d)
            d++;

        bin[d - 1]++;
    }

    for (; q; q--) {
        int b;
        get b;

        int d = 0;
        int l[32];
        rep(i, 0, 32)
            l[i] = bin[i];

        int ans = 0;

        while (b >= (1 << d)) {
            if (b & (1 << d)) {
                int needed = 1;
                for (int i = d; i >= 0; i--) {
                    if (l[i] >= needed) {
                        l[i] -= needed;
                        ans += needed;
                        goto nxt;
                    } else {
                        needed -= l[i];
                        ans += l[i];
                        l[i] = 0;
                    }

                    needed *= 2;
                }

                put -1;
                eol;
                goto nnxt;
            }
            nxt:;

            d++;
        }

        put ans;
        eol;

        nnxt:;
    }
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}