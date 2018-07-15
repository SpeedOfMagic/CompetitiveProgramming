/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Solution:
Notice that I can divide string into 2 parts with length N each. Then, by using only painting of left side,
I can find the right side I need.
So, I can brute force all paintings of right side and add them into map.
Then, I can go through all paintings of left side and make right side I need,
and count number of right side paintings that match needed one.

Also, hashing can be used to improve speed.
Time complexity: O(2 ^ N * N * log(N)).
*/
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
    str s;
    get s;
 
    map<pair<int, int>, int> pos;
    for (int mask = 0; mask < (1 << n); mask++) {
        str red = "", blue = "";
        rep(i, 0, n) {
            if (mask & (1 << i))
                red += s[i + n];
            else
                blue += s[i + n];
        }
 
        reverse(blue.begin(), blue.end());
        pos[{hashStr(red), hashStr(blue)}]++;
        //debug(hashStr(red), hashStr(blue));
    }
 
    int ans = 0;
 
    for (int mask = 0; mask < (1 << n); mask++) {
        str red = "", blue = "";
        rep(i, 0, n) {
            if (mask & (1 << i))
                red += s[i];
            else
                blue += s[i];
        }
 
        //debug(mask, red, blue);
        reverse(red.begin(), red.end());
        ans += pos[{hashStr(red), hashStr(blue)}];
    }
 
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}