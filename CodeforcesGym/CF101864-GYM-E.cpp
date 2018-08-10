/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
#define int long long
typedef long double ld;
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int mod = 1e9 + 7;
int pow(int a, int b) {
    if (b == 0)
        return 1 % mod;

    if (b % 2)
        return (a * pow(a, b - 1)) % mod;

    int res = pow(a, b / 2);

    return (res * res) % mod;
}

//uses pow
int inv(int a) {
    return pow(a, mod - 2);
}

vector<int> factorials = {1};
vector<int> invFactorials = {1};
void initFactorials(unsigned int n) { //calculates [1! % mod, 2! % mod, ... , n! % mod]
    for (unsigned int i = factorials.size(); i <= n; i++) {
        int d = factorials.back();
        factorials.push_back((d * i) % mod);
    }
}

//uses initFactorials, inv;
void initInvFactorials(unsigned int n) {
    initFactorials(n);
}

//uses initFactorials, initInvFactorials;
int c(int k, int n){
    initInvFactorials(n);

    return ((factorials[n] * inv(factorials[k])) % mod * inv(factorials[n - k])) % mod;
}

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        int n, m, k;
        read(n, m, k);
        if (k > n)
            put 0;
        else {
            put (c(k, n) * pow(m, k)) % mod;
        }
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}