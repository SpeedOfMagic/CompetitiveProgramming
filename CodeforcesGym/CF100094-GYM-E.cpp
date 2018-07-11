/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Statement:
An array (manually generated) with n (1 <= n <= 10^5) elements is given.
Process m (1 <= m <= 10^7) manually generated queries: find min(a[l], a[l + 1], ... , a[r]).

Solution:
It can be done with sparse table.
**/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
#if 1  //FileIO
const string fileName = "sparse";
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
    get a[0];
    rep(i, 1, n)
        a[i] = (23 * a[i - 1] + 21563) % 16714589;

    //for (int i : a) print(i);eol;

    const int M = 18;
    int sparse[n][M];
    rep(i, 0, n)
        rep(j, 0, M)
            sparse[i][j] = -1;
    rep(i, 0, n)
        sparse[i][0] = a[i];
    rep(j, 1, M)
        rep(i, 0, n)
            if (i + (1 << j) > n)
                break;
            else
                sparse[i][j] = min(sparse[i][j - 1], sparse[i + (1 << (j - 1))][j - 1]);

    int powerOfTwo[n + 1];
    int val[n + 1];
    int p = 0;
    rep(i, 1, n + 1) {
        if ((1 << (p + 1)) == i)
            p++;
        powerOfTwo[i] = p;
    }

    rep(i, 1, n + 1)
        val[i] = 1 << powerOfTwo[i];
    
    int u, v;
    read(u, v);
    int ans = 0;
    rep(i, 1, m) {
        int l = u - 1, r = v - 1;
        if (l > r)
            swap(l, r);

        int k = powerOfTwo[r - l + 1];
        int d = val[r - l + 1];

        ans = min(sparse[l][k], sparse[r - d + 1][k]);

        //debug(i, l, r, ans, k);
        u = ((17 * u + 751 + ans + 2 * i) % n) + 1;
        v = ((13 * v + 593 + ans + 5 * i) % n) + 1;
    }

    
    print(u, v);
    int l = u - 1, r = v - 1;
        if (l > r)
            swap(l, r);

        int k = powerOfTwo[r - l + 1];
        int d = val[r - l + 1];

        ans = min(sparse[l][k], sparse[r - d + 1][k]);
        
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}