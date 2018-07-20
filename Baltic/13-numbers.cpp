/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. To make sure that number is palindrome-free,
I can only check substrings with length 3 and 2,
because if any substring[l : r] is palindrome, then substring[l + 1 : r - 1] is also palindrome.

2. Amount of numbers in range [l : r] = amount in range[1 : r] - amount in range[1 : l].
3. Suppose there is d such that d = 10 ^ i, d <= r; d * 10 > r.
Then, amount in range[1 : r] = amount in range[1 : d - 1] + amount in range[d : r].
4. I want to calculate amount in range[d : r] with dp approach:
	Let dp[i][j][k] be:
	"Amount of free-palyndromic numbers before i-th digit, while having current digit j,
	and previous digit was k".
	
	Also, if k = 10, then there were no previous digit.
5. Then, I again divide range [d : r] in a way that based on digits of r,
	for example, 12305 [10000 : 12305] will be divided on following ranges:
	[10000 : 10000 - 1], [10000 : 12000 - 1], [12000 : 12300 - 1],
	[12300 : 12300 - 1], [12300 : 12305].
6. After that dp goes as follows:
	I set pointer p to first non-zero. Then, dp[p][j][digit[p - 1]] is set to 1,
	if it's possible to place digit j in this place.
	If p == 0, then digit[p - 1] = 10.
	Then, I increment j while it's < length(r), and for selected by brute force digits j and k,
	I go through all previous x2 digits l.
	If l != j and l != k, then dp[p][j][k] += dp[p - 1][k][l].
7. Answer is sum of sums for each digit j and k dp[n - 1][j][k] on each segment.

Time complexity: O(log10(b) ^ 3 * digitAlphabet ^ 2).
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
int solve(int r) {
    if (r <= 9)
        return r + 1;
 
    int ans = 0;
 
    int dd = 1;
    while (dd * 10 <= r)
        dd *= 10;
    ans += solve(dd - 1);
 
    vint digits;
    while (r) {
        digits.pb(r % 10);
        r /= 10;
    }
    reverse(digits.begin(), digits.end());
    int n = sz(digits);
 
    int dp[n][10][11]; //dp[i][j][k] - i-th digit; j-th cur digit; k-th cur previous digit.
    rep(i, 0, n) {
        int prob1 = (i ? digits[i - 1] : 10),
            prob2 = (i > 1 ? digits[i - 2] : 10);
 
        bool cantGoFurther = 0;
        if (digits[i] == prob1 || digits[i] == prob2)
            cantGoFurther = 1;
 
        rep(j, 0, 10) {
            rep(k, 0, 11)
                dp[i][j][k] = 0;
 
            if (digits[i] < j || (i + 1 < n && digits[i] == j) || (i == 0 && j == 0))
                continue;
 
            if (j != prob1 && j != prob2)
                dp[i][j][prob1] = 1;
        }
 
        rep(p, i + 1, n)
            rep(j, 0, 10)
                rep(k, 0, 11) {
                    dp[p][j][k] = 0;
                    if (k == 10)
                        break;
 
                    if (j != k)
                        rep(l, 0, 11)
                            if (l != j && l != k)
                                dp[p][j][k] += dp[p - 1][k][l];
                }
 
        rep(j, 0, 10)
            rep(k, 0, 10)
                ans += dp[n - 1][j][k];
 
        if (cantGoFurther)
            break;
    }
 
    return ans;
}
 
void run() {
    int a, b;
    read(a, b);
    put solve(b) - solve(a - 1);
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}