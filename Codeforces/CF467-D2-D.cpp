/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/13870
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
const int base = 29;
const int mod2 = 36028797018963913;
int hashStr(str s) {
    int hsh = 0;
    for (char i : s) {
        if (i <= 'Z')
            i = i - 'A' + 'a';
        hsh = ((hsh * base) % mod2 + i - 'a' + 1) % mod2;
    }
    return hsh;
}

const int N = 3e5 + 1;
int tot = 0;
map<int, int> convert;

vint g[N];
vint rev[N];
vint g2[N];

bool vis[N];
int color[N];
int curColor = 0;
stack<int> l;

void kosaraju(int cur, bool todo) {
    if (todo) {
        color[cur] = curColor;
        for (int i : rev[cur])
            if (color[i] == 0)
                kosaraju(i, 1);
    } else {
        vis[cur] = 1;
        for (int i : g[cur])
            if (!vis[i])
                kosaraju(i, 0);

        l.push(cur);
    }
}

pair<int, int> val[N];
pair<int, int> colorVal[N];

void dfs(int cur) {
    for (int i : g2[cur]) {
        dfs(i);
        colorVal[cur] = min(colorVal[cur], colorVal[i]);
    }
}

void run() {
    int m;
    get m;
    int toAnswer[m];
    rep(i, 0, m) {
        str s;
        get s;
        int hsh = hashStr(s);
        if (!convert.count(hsh))
            convert[hsh] = tot++;

        toAnswer[i] = convert[hsh];

        int r = 0;
        for (char j : s)
            if (j == 'r' || j == 'R')
                r++;

        val[toAnswer[i]] = {r, sz(s)};
    }

    int n;
    get n;
    for (; n; n--) {
        str x, y;
        read(x, y);

        int hshX = hashStr(x);
        if (!convert.count(hshX))
            convert[hshX] = tot++;

        int hshY = hashStr(y);
        if (!convert.count(hshY))
            convert[hshY] = tot++;

        int indX = convert[hshX];
        int indY = convert[hshY];

        g[indX].pb(indY);
        rev[indY].pb(indX);

        int r = 0;
        for (char i : x)
            if (i == 'r' || i == 'R')
                r++;

        val[indX] = {r, sz(x)};

        r = 0;
        for (char i : y)
            if (i == 'r' || i == 'R')
                r++;

        val[indY] = {r, sz(y)};
    }

    rep(i, 0, tot) {
        vis[i] = 0;
        color[i] = 0;
    }

    rep(i, 0, tot)
        if (!vis[i])
            kosaraju(i, 0);

    while (!l.empty()) {
        int p = l.top();
        l.pop();
        if (color[p] == 0) {
            curColor++;
            kosaraju(p, 1);
        }
    }
    curColor++;
    rep(i, 1, curColor)
        colorVal[i] = {inf, inf};

    rep(i, 0, tot) {
        vis[i] = 0;
        colorVal[color[i]] = min(colorVal[color[i]], val[i]);
        for (int j : g[i])
            if (color[i] != color[j])
                g2[color[i]].pb(color[j]);
    }

    rep(i, 1, curColor)
        if (!vis[i])
            dfs(i);

    int ans1 = 0, ans2 = 0;
    //debug(m, curColor, tot);
    for (int i : toAnswer) {
        ans1 += colorVal[color[i]].first;
        ans2 += colorVal[color[i]].second;
    }

    print(ans1, ans2);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
