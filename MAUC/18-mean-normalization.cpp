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
    //thinking: 1 min
    int n;
    get n;
    pair<int, int> mean[n];
    vint p;
    rep(i, 0, n) {
        int m;
        get m;
        int s = 0;
        rep(j, 0, m) {
            p.pb(getInt());
            s += p.back();
        }
        mean[i] = {s, m};
    }

    sort(p.begin(), p.end());
    sort(mean, mean + n, [](pair<int, int> a, pair<int, int> b) {
        int v1 = a.fs * b.sc;
        int v2 = b.fs * a.sc;
        return v1 < v2;
    });
    int s = 0;
    int m = sz(p);
    rep(i, 0, m)
        s += p[i];

    int cur = 0;
    ld ans = 1e18;
    rep(i, 0, n) {
        while (cur < m) {
            int v1 = mean[i].fs, v2 = p[cur] * mean[i].sc;
            if (v1 >= v2) {
                s -= p[cur] * 2;
                cur++;
            } else
                break;
        }
        ld val = mean[i].fs;
        val /= mean[i].sc;
        ans = min(ans, s + cur * val - (m - cur) * (val));
    }
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}