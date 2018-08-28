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
const long long base = 27;
const int lim = 5;
void run() {
    int n;
    get n;
    set<int> pos;
    int pows[lim];
    pows[0] = 1;
    rep(i, 1, lim)
        pows[i] = pows[i - 1] * base;
	int powsMul[lim];
	rep(i, 0, lim)
    	powsMul[i] = pows[i] * 25ll;
    rep(i, 0, n) {
        str s;
        get s;
        rep(j, 1, lim) {
            int curHsh = 0;
            rep(k, 0, j)
                curHsh = curHsh * base, curHsh += (s[k] - 'a' + 1);
            pos.insert(curHsh);
            rep(k, j, sz(s)) {
                int z = s[k - j] - 'a' + 1;
                curHsh -= pows[j - 1] * z;
                curHsh = curHsh * base;
                curHsh += (s[k] - 'a' + 1);
                pos.insert(curHsh);
            }
        }
    }
    str cur = "a";
    int hsh = 1;
    while (1) {
        if (pos.count(hsh)) {
            for (int j = sz(cur) - 1; j >= 0; j--) {
                if (cur[j] != 'z') {
                    cur[j]++;
                    hsh += pows[sz(cur) - j - 1];
                    goto nxt;
                } else {
                    hsh -= powsMul[sz(cur) - j - 1];
                    cur[j] = 'a';
                }
            }
            hsh += pows[sz(cur)];
            cur += "a";
            nxt:;
        } else {
            put cur;
            return;
        }
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
