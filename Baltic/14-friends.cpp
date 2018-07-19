/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. It's obvious that T totally depends on S, then I can determine S by converting U to T.
2. That means, by only removing one letter from any position, I can determine if such string is possible.
3. So, I want to go over all letters and try to remove them, then check if resulting string can be done by copying.
4. To quickly check if resulting string can be done by copying, I can compare first and second half of it.
And to quickly compare first and second half of it, I can use polynomial hashing property that:
hash(S[l : r]) = (hash(S[1 : r]) - hash(S[1 : l - 1]) * (base ^ (r - l + 1)) + mod) % mod.
Since r - l + 1 <= n, then base ^ (r - l + 1) can be precalculated.

5. If strings are equal (hashes are also equal), then I check answer.
If it's empty, then I fill it and calculate its hash.
Else I compare answer's hash and resulting string hash (both are already calculated).
If they differ, then answer is "NO UNIQUE". Otherwise, nothing is changed.

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
const long long mod1 = 1999998893;
const long long mod2 = 2100003611;
const long long base = 29;
const char startingLetter = 'A'; //starting letter of the alphabet
 
long long hashChar(char c){
    return c - startingLetter + 1;
}
 
pair<long long, long long> hashStr(pair<long long, long long> prevHash, char curChar) {
    return {((prevHash.first * base) % mod1 + hashChar(curChar)) % mod1,
            ((prevHash.second * base) % mod2 + hashChar(curChar)) % mod2};
}
 
const int N = 2e6 + 1;
int powOfBase1[N], powOfBase2[N];
 
void run() {
    int n;
    get n;
    str u;
    get u;
 
    powOfBase1[0] = 1;
    powOfBase2[0] = 1;
    rep(i, 1, n + 1) {
        powOfBase1[i] = (base * powOfBase1[i - 1]) % mod1;
        powOfBase2[i] = (base * powOfBase2[i - 1]) % mod2;
    }
 
    str left = "", right = "";
    rep(i, 0, n / 2 + 1)
        left += u[i];
 
    rep(i, n / 2 + 1, n)
        right += u[i];
 
    str ans = "";
    pair<int, int> ansHsh = {0, 0};
 
    rep(z, 0, 2) {
        v<pair<int, int>> hshLeft, hshRight;
        hshLeft.pb({hashChar(left[0]), hashChar(left[0])});
        rep(i, 1, sz(left)) {
            auto d = hshLeft.back();
            hshLeft.pb(hashStr(d, left[i]));
        }
 
        hshRight.pb({hashChar(right[0]), hashChar(right[0])});
        rep(i, 1, sz(right)) {
            auto d = hshRight.back();
            hshRight.pb(hashStr(d, right[i]));
        }
 
        if (z) {
            //debug(sz(hshRight), right, sz(hshLeft), left);
            rep(i, 1, sz(right)) {
                auto resultHash = hshRight.back();
                int offset = sz(right) - (i + 1);
                resultHash.first =
                ((resultHash.first - (powOfBase1[offset] * hshRight[i].first) % mod1) % mod1 + mod1) % mod1;
 
                if (i)
                    resultHash.first = (resultHash.first + (powOfBase1[offset] * hshRight[i - 1].first) % mod1) % mod1;
 
                resultHash.second =
                ((resultHash.second - (powOfBase2[offset] * hshRight[i].second) % mod2) % mod2 + mod2) % mod2;
 
                if (i)
                    resultHash.second = (resultHash.second + (powOfBase2[offset] * hshRight[i - 1].second) % mod2) % mod2;
 
                if (resultHash == hshLeft.back()) {
                    if (ans == "") {
                        rep(j, 0, sz(right))
                            if (i != j)
                                ans += right[j];
                        for (char j : ans)
                            ansHsh = hashStr(ansHsh, j);
                    } else {
                        if (resultHash != ansHsh) {
                            put "NOT UNIQUE";
                            return;
                        }
                    }
                }
 
            }
        } else {
            rep(i, 0, sz(left)) {
                auto resultHash = hshLeft.back();
                int offset = sz(left) - (i + 1);
                resultHash.first =
                ((resultHash.first - (powOfBase1[offset] * hshLeft[i].first) % mod1) % mod1 + mod1) % mod1;
 
                if (i)
                    resultHash.first = (resultHash.first + (powOfBase1[offset] * hshLeft[i - 1].first) % mod1) % mod1;
 
                resultHash.second =
                ((resultHash.second - (powOfBase2[offset] * hshLeft[i].second) % mod2) % mod2 + mod2) % mod2;
 
                if (i)
                    resultHash.second = (resultHash.second + (powOfBase2[offset] * hshLeft[i - 1].second) % mod2) % mod2;
 
                if (resultHash == hshRight.back()) {
                    if (ans == "") {
                        rep(j, 0, sz(left))
                            if (i != j)
                                ans += left[j];
                        for (char j : ans)
                            ansHsh = hashStr(ansHsh, j);
                    } else {
                        if (resultHash != ansHsh) {
                            put "NOT UNIQUE";
                            return;
                        }
                    }
 
                }
 
            }
        }
 
        if (z)
            break;
 
        right = left.back() + right;
        left.pop_back();
    }
    //debug(ans[0]);
    if (sz(ans) == 0)
        put "NOT POSSIBLE";
    else
        put ans;
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}