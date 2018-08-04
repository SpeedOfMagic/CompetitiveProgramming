/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Solution:
1. It's possible to notice that if both of them play optimally, then there are at most n final states.

2. I want to get all states, get possible score from them, and then sort them in decreasing order of score.
It can be optimally and easily done by keeping current sum.

3. Now, for each i in [0 : n - 1] I want to find out if it's possible to get one of first i states.

4. Notice that each computer is contained in at most ceil(n / 2) states.
I want to prove that if this computer will paricipate in every possible state, then, if hacker will choose this computer,
then it's impossible for operator to not let him get any of states this computer has.

5. So, to do that, I can keep an array and increment every index which paricipates in state #i.
If at least any index will encounter ceil(n / 2) times, then answer is score of state #i. Else, I'll continue doing that.

6. To make it optimal, it's easy to notice that all indexes form contigous segment,
where values n - 1 and 0 are considered contigous.
So, I need to proccess 2 queries:
	1. l r - add 1 to segment [l : r]
	2. Check if any value in the array >= ceil(n / 2).

7. It's easy to transform circle segment [l : r] in segments [l : n - 1] and [0 : r] (if l > r).
Also, it's enough to find maximum of all values in the array.

8. Both of these queries can be optimally done with lazy segment tree.
Time complexity: O(n * log n).
**/
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
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
char curFlag = 'A'; void flag() {put curFlag++ << endl;}
int getInt(){int a; get a; return a;}
//code goes here
int f(int a, int b) { //f - query you need to calculate, but for two values
    return max(a, b);
}
const int nothing = 0; //nothing means that f(x, nothing)=x
struct segTreeNode {
    int val = nothing, lazy = 0;
 
    segTreeNode(){}
 
    void update(int s) { //function that updates single node from lazy
        val += s;
    }
};
 
v<segTreeNode> segTree;
int n, tot;
 
void update(int l, int r, int s, int cur = 1, int ll = 1, int rr = tot) {
    if (segTree[cur].lazy != 0) {
        segTree[cur].update(segTree[cur].lazy);
        if(cur < tot) {
            segTree[cur * 2].lazy += segTree[cur].lazy;
            segTree[cur * 2 + 1].lazy += segTree[cur].lazy;
        }
        segTree[cur].lazy = 0;
    }
 
    if (l > r)
        return;
 
    if (l == ll && r == rr) {
        segTree[cur].update(s);
        if (cur < tot) {
            segTree[cur * 2].lazy += s;
            segTree[cur * 2 + 1].lazy += s;
        }
        return;
    }
 
    int mid = (ll + rr) / 2;
    update(l, min(r, mid), s, cur * 2, ll, mid);
    update(max(l, mid + 1), r, s, cur * 2 + 1, mid + 1, rr);
    segTree[cur].val = f(segTree[cur * 2].val, segTree[cur * 2 + 1].val);
}
 
int query(int l, int r, int cur = 1, int ll = 1, int rr = tot) {
    assert(l >= ll && r <= rr);
    if (segTree[cur].lazy != 0) {
        segTree[cur].update(segTree[cur].lazy);
        if (cur < tot) {
            segTree[cur * 2].lazy += segTree[cur].lazy;
            segTree[cur * 2 + 1].lazy += segTree[cur].lazy;
        }
        segTree[cur].lazy = 0;
    }
 
    if (l > r)
        return nothing;
 
    if (l == ll && r == rr)
        return segTree[cur].val;
 
    int mid = (ll + rr) / 2;
 
    return f(query(l, min(r, mid), cur * 2, ll, mid), query(max(l, mid + 1), r, cur * 2 + 1, mid + 1, rr));
    segTree[cur].val = f(segTree[cur * 2].val, segTree[cur * 2 + 1].val);
}
 
void init(vector<int> vals) {
    n = vals.size();
    tot = n;
    while(tot & (tot - 1))
        tot++;
 
    segTree = vector<segTreeNode>(2 * tot);
    rep(i, tot, tot + n)
        segTree[i].val = vals[i - tot];
 
    for(int i = tot - 1; i; i--)
        segTree[i].val = f(segTree[i * 2].val, segTree[i * 2 + 1].val);
}
 
void run() {
    get n;
    int v[n];
    rep(i, 0, n)
        get v[i];
    init(vint(n, 0));
    vint d[n];
    int s = 0;
    rep(j, 0, n / 2 + n % 2)
        s += v[j];
    rep(i, 0, n) {
        if (i)
            s = s - v[i - 1] + v[(i + n / 2 + n % 2 - 1 + n) % n];
        d[i] = {s, i, (i + n / 2 + n % 2 - 1 + n) % n};
    }
 
 
    sort(d, d + n);
    for (int i = n - 1; i >= 0; i--) {
        //debug(d[i][0], d[i][1] + 1, d[i][2] + 1);
        if (d[i][1] > d[i][2]) {
            update(d[i][1] + 1, n, 1);
            update(1, d[i][2] + 1, 1);
        } else {
            update(d[i][1] + 1, d[i][2] + 1, 1);
        }
 
        if (query(1, n) == n / 2 + n % 2) {
            put d[i][0];
            return;
        }
    }
}
 
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}