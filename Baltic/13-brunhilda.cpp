/** MIT License Copyright (c) 2018-2019 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
//#define int long long
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
const long long N = 1e7 + 1;

void run() {
    int m, q;
    read(m, q);
 
    int p[m];
    rep(i, 0, m) 
        get p[i];
    
    long long mul = 1;
    rep(i, 0, m) {
        mul *= p[i];
        if (mul > N) {
            mul = 1e9;
            break;
        }
    }
    
    vint order;
    int n = 0;
    while (n < min(N, mul - 1)) {
        order.pb(n);
        int d = 0;
        for (int i : p)
            d = max(d, n / i * i + i - 1);
        n = d;
    }
 
    rep(i, 0, q) {
        int n;
        get n;
        if (n >= mul)
            put "oo";
        else
            put lower_bound(order.begin(), order.end(), n) - order.begin();
        eol;
    }
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); run();}