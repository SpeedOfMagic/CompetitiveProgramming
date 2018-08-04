/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/55362
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
    return a + b;
}
const int nothing = 0; //nothing means that f(x, nothing)=x
struct segTreeNode {
    int val = nothing, lazy = 0;
    segTreeNode(){}
    void update(int l, int r) { //function that updates single node from lazy
        this->val = (r - l + 1) - this -> val;
    }
};
v<segTreeNode> segTree;
int n, tot;
void update(int l, int r, int cur = 1, int ll = 1, int rr = tot){
    //debug(l, r, cur, ll, rr, segTree[cur].val, segTree[cur].lazy);
    bool finish = 0;
    if (l == ll && r == rr) {
        segTree[cur].lazy++;
        finish = 1;
    }

    segTree[cur].lazy %= 2;
    if(segTree[cur].lazy != 0) {
        segTree[cur].update(ll, rr);
        if(cur < tot){
            segTree[cur * 2].lazy++;
            segTree[cur * 2 + 1].lazy++;
        }
        segTree[cur].lazy = 0;
    }
    if(l > r || finish)
        return;



    int p = (ll + rr) / 2;

    update(l, min(r, p), cur * 2, ll, p);
    update(max(l, p + 1), r, cur * 2 + 1, p + 1, rr);

    segTree[cur].val = segTree[cur * 2].val + segTree[cur * 2 + 1].val;

}
int query(int l, int r, int cur = 1, int ll = 1, int rr = tot){
    segTree[cur].lazy %= 2;
    if(segTree[cur].lazy != 0) {
        segTree[cur].update(ll, rr);
        if(cur < tot){
            segTree[cur * 2].lazy++;
            segTree[cur * 2 + 1].lazy++;
        }
        segTree[cur].lazy = 0;
    }
    if(l > r)
        return nothing;

    int p = (ll + rr) / 2;
    if(l == ll && r == rr)
        return segTree[cur].val;

    return f(query(l, min(r, p), cur * 2, ll, p), query(max(l, p + 1), r, cur * 2 + 1, p + 1, rr));
}
void init(){
    tot=n - 1;
    while(tot&(tot-1))tot++;
    segTree=vector<segTreeNode>(2*tot);
    rep(i,tot,tot+n - 1)segTree[i].val = 0;
    for(int i=tot-1;i;i--)segTree[i].val=f(segTree[i*2].val,segTree[i*2+1].val);
}

const int N = 2e5 + 1;
int lll[N];
int rrr[N];

vint g[N];

int p = 1;

void dfs(int cur = 1) {
    lll[cur] = p++;
    for (int i : g[cur])
        dfs(i);
    rrr[cur] = p - 1;
}

void run() {
    get n;
    n++;

    rep(i, 2, n) {
        int p;
        get p;
        g[p].pb(i);
    }

    dfs();
    init();

    rep(i, 1, n) {
        int t;
        get t;
        if (t == 1)
            update(lll[i], lll[i]);
    }

    int q;
    get q;
    for (; q; q--) {
        str quer;
        get quer;

        int v;
        get v;
        if (quer == "pow")
            update(lll[v], rrr[v]);
        else
            put query(lll[v], rrr[v]), eol;
    }

}


int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}