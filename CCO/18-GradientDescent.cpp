/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/** Solution:
1. It's easy to prove that resulting point is median in elements in Ox and in Oy.
2. To find it for Ox, I need to find such position (x; y), that cost((x; y)) < cost((x + 1; y)).
It can be done by binary search. The same applies to Oy.
3. This uses 2 * log(r) + 2 * log(c) queries. To reduce amount,
I can note that Ox and Oy are independent from each other, => I can process both binary searches in parallel.
This uses log(max(r, c)) + log(r) + log(c) queries, which is enough for AC.
**/
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
    int r, c, k;
    read(r, c, k);
    int ly = 1, ry = r, lx = 1, rx = c;
    while (ly < ry || lx < rx) {
        int midx = (lx + rx) / 2;
        int midy = (ly + ry) / 2;
        debug("?", midy, midx);
        int v;
        get v;
        if (ly < ry) {
            debug("?", midy + 1, midx);
            int v2;
            get v2;
            if (v <= v2)
                ry = midy;
            else
                ly = midy + 1;
        }

        if (lx < rx) {
            debug("?", midy, midx + 1);
            int v2;
            get v2;
            if (v <= v2)
                rx = midx;
            else
                lx = midx + 1;
        }
    }
    int v;
    debug("?", ry, rx);
    get v;
    debug("!", v);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
