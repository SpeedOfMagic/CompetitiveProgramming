/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
Since n is small, then there should be brute force.
Since matches are independent from each other,
then I can use meet-in-the-middle tecnique to process the bruteforce quickly.

I divide all possible combinations of matches in 2 parts: left and right.
Then, for each element in left, I get its price,
and I need to find amount of elements in right with <= m - <price of element in left>.
It can be done by simple upper_bound.

Time complexity: O(sqrt(2 ^ n) * log(sqrt(2 ^ n))).
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
    int n, m;
    read(n, m);
    int a[n];
    rep(i, 0, n)
        get a[i];

    int v = n / 2;
    vint left, right;
    for (int mask = 0; mask < (1 << v); mask++) {
        int price = 0;
        rep(i, 0, v)
            if (mask & (1 << i))
                price += a[i];
        left.pb(price);
    }

    for (int mask = 0; mask < (1 << (n - v)); mask++) {
        int price = 0;
        rep(i, v, n)
            if (mask & (1 << (i - v)))
                price += a[i];
        right.pb(price);
    }

    sort(left.begin(), left.end());
    sort(right.begin(), right.end());

    int ans = 0;

    rep(i, 0, sz(left)) {
        int may = m - left[i];
        int ind = upper_bound(right.begin(), right.end(), may) - right.begin();
        ans += ind;
    }

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
