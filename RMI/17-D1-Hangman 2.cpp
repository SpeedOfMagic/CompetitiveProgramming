/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    char ans[30001];
    int initHsh[30001];
    int hsh[30001];
    const int base = 29;
    const int mod = 36028797018963913;
    int powOfBase[30001];
    powOfBase[0] = 1;
    rep(i, 1, 30001)
        powOfBase[i] = (powOfBase[i - 1] * base) % mod;

    int t;
    get t;
    for (; t; t--) {
        int n, k;
        read(n, k);
        str s[n];
        rep(i, 0, n)
            get s[i];

        memset(ans, 0, sizeof(ans));
        if (n > k) {
            memset(initHsh, 0, sizeof(initHsh));
            rep(i, 0, n)
                rep(j, 0, k)
                    initHsh[i] = (initHsh[i]  + ((s[i][j] - 'a' + 1) * powOfBase[j]) % mod) % mod;

            rep(j1, 0, k)
                rep(j2, j1 + 1, k) {
                    hmap<int, int> posHsh;
                    rep(i, 0, n) {
                        hsh[i] = initHsh[i];
                        hsh[i] = (hsh[i] - (powOfBase[j1] * (s[i][j1] - 'a' + 1)) % mod + mod) % mod;
                        hsh[i] = (hsh[i] - (powOfBase[j2] * (s[i][j2] - 'a' + 1)) % mod + mod) % mod;
                        posHsh[hsh[i]]++;
                    }
                    rep(i, 0, n)
                        if (posHsh[hsh[i]] > 1)
                            ans[i] = 1;
                }

        } else {
            rep(i, 0, n)
                rep(j, i + 1, n) {
                    int dif = 0;
                    rep(l, 0, k)
                        if (s[i][l] != s[j][l])
                            dif++;

                    if (dif <= 2)
                        ans[i] = ans[j] = 1;
                }
        }
        rep(i, 0, n)
            if (ans[i])
                put 1;
            else
                put 0;
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
