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

const long long mod2 = 36028797018963913; //2^55-55
const long long base = 29; //alphabet size
const char startingLetter = 'a'; //starting letter of the alphabet

long long hashChar(char c){
    return c - startingLetter + 1;
}

long long hashStr(long long prevHash, char curChar){
    return ((prevHash * 29) % mod2 + hashChar(curChar)) % mod2;
}

long long hashStr(string& s){
    long long res = 0;
    for(char i : s)
        res = hashStr(res, i);
    return res;
}


void run() {
    int n;
    get n;

    int siz[n];
    int hsh[n];
    rep(i, 0, n) {
        str s;
        get s;
        siz[i] = sz(s);
        hsh[i] = hashStr(s);
    }
    int s = -1;
    rep(i, 0, n)
        s += siz[i] + 1;

    int ans = s;
    rep(l, 0, n)
        rep(r, l, n) {
            vint seq;
            rep(i, l, r + 1)
                seq.pb(hsh[i]);
            seq.pb(-inf);
            rep(i, 0, n)
                seq.pb(hsh[i]);

            int m = sz(seq);

            vint Z = vint(m);

            int ll = 0, rr = 0;

            rep(i, 1, m) {
                if (i > rr || Z[i-ll] >= rr - i + 1) {
                    rr = max(rr,i);
                    ll = i;

                    while (rr < m && seq[rr-ll] == seq[rr])
                        rr++;

                    Z[i] = rr -i;

                    rr--;
                } else
                    Z[i] = Z[i-ll];
            }

            int dp[m];
            rep(i, 0, m)
                dp[i] = 0;

            rep(i, 0, r - l + 1)
                Z[i] = 0;
                
            rep(i, r - l + 2, m) {
                dp[i] = dp[i - 1];
                if (Z[i] >= r - l + 1)
                    dp[i] = max(dp[i - (r - l + 1)] + 1, dp[i]);
            }

            int length = -1;
            rep(i, l, r + 1)
                length += siz[i] + 1;
            length -= (r - l + 1);

            int amount = dp[m - 1];
            int pos = s - length * amount;

            if (amount >= 2){
                ans = min(ans, pos);
                //debug(l, r, amount, pos);
            }
        }
    put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}