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
    int n;
    get n;
    int b[n];
    rep(i, 0, n)
        get b[i];

    int a[n];

    int m = n;
    while (m & (m - 1))
        m++;

    int siz[m * 2];
    memset(siz, 0, sizeof(siz));
    rep(i, 0, n)
        siz[i + m] = 1;
    for (int i = m - 1; i; i--)
        siz[i] = siz[i * 2] + siz[i * 2 + 1];

    for (int i = n - 1; i >= 0; i--) {
        int cur = 1;
        while (cur < m) {
            siz[cur]--;
            if (siz[cur * 2 + 1] > b[i])
                cur = cur * 2 + 1;
            else {
                b[i] -= siz[cur * 2 + 1];
                cur = cur * 2;
            }
        }
        siz[cur]--;
        if (b[i]) {
            put "NIE";
            return;
        }
        a[i] = cur - m + 1;
    }

    rep(i, 0, n) put a[i] << '\n';
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
