/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
Firstly, I want to sort the entire array first.
Then, I keep 2 pointers to maintain the segment of equal elements. If next element will be higher,
then i'll add segment's length to amount of possible places to insert element.
After that, I'll try to insert element i'm currently pointing to, to any possible place,
and decrement amount of possible places by 1 after that.

Time complexity: O(n * log n)
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
    int n;
    get n;
    int a[n];
    rep(i, 0, n)
    get a[i];
    int b[n];
    rep(i, 0, n)
    b[i] = a[i];
    sort(b, b + n);
    int posPlaces = 0;
    int ans = 0;
    int l = 0;
    rep(r, 1, n) {
        if (b[r] != b[l]) {
            posPlaces+= r-l;
            l = r;
        }

        if (posPlaces > 0) {
            posPlaces--;
            ans++;
        }
    }
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}