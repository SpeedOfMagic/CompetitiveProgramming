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
bool valid(str t, int a, int b) {
    for (char i : t)
        if (i > '9' || i < '0')
            return 0;
    int left = 0, right = sz(t) - 1;
    for (int i = 1; i < sz(t); i++)
        if (t[left] > t[i])
            left = i;
    for (int i = sz(t) - 1; i >= 0; i--)
        if (t[right] < t[i])
            right = i;
    return (left == a && right == b);

}
void run() {
    str s;
    get s;
    int n = sz(s);
    v<str> ans;
    rep(a, 0, n)
        rep(b, 0, n) {
            str t = s;
            swap(t[a], t[b]);
            v<str> pos;
            if (t[a] == '9') {
                if (t[b] == '0') {
                    if (valid(t, a, b))
                        ans.pb(t);
                    t[b]++;
                    if (valid(t, a, b))
                        ans.pb(t);
                    t[b]--;
                    t[a]--;
                    if (valid(t, a, b))
                        ans.pb(t);
                    t[b]++;
                    if (valid(t, a, b))
                        ans.pb(t);
                } else {
                    t[b]++;
                    if (valid(t, a, b))
                        ans.pb(t);
                    t[a]--;
                    if (valid(t, a, b))
                        ans.pb(t);
                }
            } else {
                if (t[b] == '0') {
                    t[a]--;
                    if (valid(t, a, b))
                        ans.pb(t);
                    t[b]++;
                    if (valid(t, a, b))
                        ans.pb(t);
                } else {
                    t[a]--;
                    t[b]++;
                    if (valid(t, a, b))
                        ans.pb(t);
                }
            }
        }
    sort(ans.begin(), ans.end());
    if (ans.empty())
        put -1;
    for (str i : ans)
        put i << endl;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
