/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. Obviously, answer is difficulty of entire path with all possible bitmasks of break locations.
2. Also, answer can be represented as k[0] * a[0] + k[1] * a[1] + ... + k[n-1] * a[n-1]
So, I want to find k[0], k[1], ..., k[n-1].
3. By using brute force with O(2^n) complexity I can get the following sequence when n = 7:
576, 256, 112, 48, 20, 8, 3, 1.
Based on that it's reversed A001792 sequence (https://oeis.org/A001792)
with b(n) = (n + 2) * 2 ^ (n - 1), starting with n = 0.
=> k[i] = b(n - i - 1).
Time complexity: O(n).
**/
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
void run() {
    const int mod = 998244353;
    int n;
    get n;
    int a[n];
    rep(i, 0, n)
        get a[i];

    int ans = a[n - 1];
    reverse(a, a + n);

    int curPow = 1;
    rep(i, 1, n) {
        ans = (ans + (a[i] * ((curPow * (i + 2)) % mod)) % mod) % mod;
        curPow = (curPow * 2) % mod;
    }

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}