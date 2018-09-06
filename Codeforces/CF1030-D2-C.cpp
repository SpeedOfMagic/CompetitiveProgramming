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
    int a[n];
    rep(i, 0, n)
        get a[i];
    int b[n];
    rep(i, 0, n)
        get b[i];
    sort(a, a + n);
    sort(b, b + n);

    int p1 = n - 1, p2 = n - 1;
    int res = 0;
    bool turn = 0;
    while (p1 >= 0 || p2 >= 0)
        if (turn == 0) {
            if ((p2 != -1) && (p1 == -1 || b[p2] > a[p1]))
                p2--;
            else {
                res += a[p1];
                p1--;
            }
            turn = 1;
        } else {
            if ((p1 != -1) && (p2 == -1 || b[p2] < a[p1]))
                p1--;
            else {
                res -= b[p2];
                p2--;
            }
            turn = 0;
        }
    put res;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}