/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution (mostly taken from https://github.com/nya-nya-meow/CompetitiveProgramming/blob/master/Kattis/lazylearner.cpp):

1. Suppose we have a substring [l, r] and a word W. It is easy to check in linear time if W is a subsequence of [l, r] or not.
2. We will solve this problem in offline. Sort all the words in lexicographical order, then sort queries by l then by r. When a new l comes, everything should be resetted.
3. Let's keep n pointers, each corresponding to a word. Each time we move ahead one character, we will move all the corresponding pointers.
4. If a pointer moves to the end of the word, that word is now a subsequence, and we will push it in our list of "for answering".
5. To answer queries in solve time, we will need online k-th order statistics. Since elements <= n, it can be done by using segment tree. Also it's possible to do that with a treap.

Time complexity: O(|S| * ((sum of sizes of all strings in dictionary) + n * log n) + q log n)
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
typedef long long ll;
//#define int ll
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
#define sz(a) ((int) a.size())
const long long inf = 4611686018427387903; //2^62 - 1
const long double EPS = 1e-12;
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//code starts here
const int N = 32768;
int val[N * 2];

void run() {
    int n, q;
    str s;
    get s;
    read(n, q);
    str t[n];
    rep(i, 0, n)
        get t[i];

    sort(t, t + n);

    vint queries[q];
    rep(i, 0, q) {
        int l, r, k;
        read(l, r, k);
        l--; r--;
        queries[i] = {l, r, k, i};
    }
    sort(queries, queries + q);

    int cl = -1, cr = -1;
    int p[n];
    str ans[q];
    vint cur[26];
    rep(que, 0, q) {
        int l = queries[que][0], r = queries[que][1], k = queries[que][2], ind = queries[que][3];
        if (cl != l) {
            memset(val, 0, sizeof val);
            memset(p, 0, sizeof p);
            cl = l;
            cr = l - 1;
            rep(j, 0, 26)
                cur[j].clear();
            rep(j, 0, n)
                cur[t[j][0] - 'a'].pb(j);
        }

        while (cr < r) {
            cr++;
            vint toAdd;
            for (int j : cur[s[cr] - 'a']) {
                p[j]++;
                if (p[j] == sz(t[j]))
                    for (int z = N + j; z; z >>= 1)
                        val[z]++;
                else
                    toAdd.pb(j);
            }
            cur[s[cr] - 'a'].clear();

            for (int j : toAdd)
                cur[t[j][p[j]] - 'a'].pb(j);
        }

        int cind = 1;
        if (val[cind] < k)
            ans[ind] = "NO SUCH WORD";
        else {
            while (cind < N) {
                if (val[cind << 1] < k) {
                    k -= val[cind << 1];
                    cind = cind << 1 | 1;
                } else
                    cind <<= 1;
            }
            assert(val[cind] == 1 && k == 1);

            ans[ind] = "";
            rep(j, 0, min(10, sz(t[cind - N])))
                ans[ind] += t[cind - N][j];
        }
    }

    rep(i, 0, q)
        put ans[i], eol;
}
signed main() {ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
