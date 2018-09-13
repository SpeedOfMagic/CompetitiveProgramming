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
    int a[n], b[n], c[n], d[n];
    rep(i, 0, n)
        read(a[i], b[i], c[i], d[i]);

    int ansx[n], ansy[n];

    rep(z, 0, 2) {
        vint ev[n];
        rep(i, 0, n)
            if (z)
                ev[i] = {b[i], d[i], i};
            else
                ev[i] = {a[i], c[i], i};

        sort(ev, ev + n);
        int p = 0;

        set<pair<int, int>> nxt;
        rep(i, 1, n + 1) {
            while (p < n && ev[p][0] == i) {
                nxt.insert({ev[p][1], ev[p][2]});
                p++;
            }

            while (!nxt.empty() && (*nxt.begin()).fs < i) {
                pair<int, int> el = *nxt.begin();
                nxt.erase(el);
            }

            if (nxt.empty()) {put "NIE"; return;}
            else {
                pair<int, int> el = *nxt.begin();
                //debug(i, el.sc);
                nxt.erase(el);
                if (z)
                    ansy[el.sc] = i;
                else
                    ansx[el.sc] = i;
            }
        }
    }

    rep(i, 0, n)
        debug(ansx[i], ansy[i]);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}