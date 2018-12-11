/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
typedef long long longlong;
//#define int longlong
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
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
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
//code goes here
const int N = 2e5 + 1;
vint t[N];
char has[N];
int amount[N];
char other[N];
int findAmount(int cur, int p) {
    amount[cur] = has[cur];
    for (int i : t[cur])
        if (i != p)
            amount[cur] += findAmount(i, cur);
    return amount[cur];
}

void fillElements(int cur, int p, queue<int>& toFill) {
    if (has[cur]) {
        toFill.push(cur);
        other[cur] = 1;
    }
    for (int i : t[cur])
        if (i != p)
            fillElements(i, cur, toFill);
}

int n, k;
void findAns(int cur, int p) {
    assert(k - amount[cur] <= k / 2);
    v<queue<int>> arr;
    priority_queue<pair<int, int>> siz;
    for (int i : t[cur])
        if (i != p && amount[i] > k / 2) {
            findAns(i, cur);
            return;
        }
    memset(other, 0, sizeof other);
    for (int i : t[cur])
        if (i != p) {
            arr.pb(queue<int>());
            fillElements(i, cur, arr.back());
            assert(sz(arr.back()) == amount[i]);
            siz.push({amount[i], sz(arr) - 1});
        }

    if (has[cur]) {
        arr.pb(queue<int>());
        arr.back().push(cur);
        siz.push({1, sz(arr) - 1});
        other[cur] = 1;
    }
    arr.pb(queue<int>());
    for (int i = 1; i <= n; i++)
        if (other[i] == 0 && has[i])
            arr.back().push(i);
    siz.push({sz(arr.back()), sz(arr) - 1});

    put 1; eol;
    put cur; eol;

    for (int i = 0; i < k / 2; i++) {
        int f = siz.top().sc;
        siz.pop();
        int s = siz.top().sc;
        siz.pop();
        print(arr[f].front(), arr[s].front(), cur);
        eol;
        arr[f].pop();
        arr[s].pop();
        siz.push({sz(arr[f]), f});
        siz.push({sz(arr[s]), s});
    }
    assert(siz.top().fs == 0);
}
void run() {
    read(n, k);
    k *= 2;
    memset(has, 0, sizeof has);
    rep(i, 1, n) {
        int v, u;
        read(v, u);
        t[v].pb(u);
        t[u].pb(v);
    }
    rep(i, 0, k) {
        int c;
        get c;
        has[c] = 1;
    }
    memset(amount, 0, sizeof amount);
    findAmount(1, -1);
    findAns(1, -1);
}
signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run(); return 0;}