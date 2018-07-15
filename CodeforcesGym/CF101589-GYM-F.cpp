/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
#if 1  //FileIO
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
int n, m;

bool valid(int r, int c) {
    return r >= 0 && r <= n - 1 && c >= 0 && c <= m - 1;
}

v<pair<int, int>> neighbours(int r, int c) {
    v<pair<int, int>> res;
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (((i == 0) ^ (j == 0)) && valid(r + i, c + j))
                res.pb({r + i, c + j});

    return res;
}

int mp[200][200];
queue<pair<int, int>> ones;

v<pair<int, int>> ans;
bool decrease(int r, int c) {
    ans.pb({r + 1, c + 1});

    mp[r][c]--;
    if (mp[r][c] == 1)
        ones.push({r, c});

    for (pair<int, int> i : neighbours(r, c)) {
        int pr = i.first, pc = i.second;
        //debug(r, c, pr, pc, mp[pr][pc]);
        if (mp[pr][pc] == 1) {
            put "No solution";
            return 0;
        } else {
            mp[pr][pc]--;
            if (mp[pr][pc] == 1)
                ones.push({pr, pc});
        }
    }

    return 1;
}

void run() {
    read(n, m);

    rep(i, 0, n)
        rep(j, 0, m)
            get mp[i][j];

    //debug(mp[2][0]);

    rep(i, 0, n)
        rep(j, 0, m)
            if (mp[i][j] == 1)
                ones.push({i, j});

    queue<pair<int, int>> full;
    rep(i, 0, n)
        rep(j, 0, m)
            if (sz(neighbours(i, j)) + 1 == mp[i][j])
                full.push({i, j});

    int nonZero = n * m;
    while (nonZero) {
        if (ones.empty()) {
            put "No solution";
            return;
        }

        while (!ones.empty()) {
            int r = ones.front().first;
            int c = ones.front().second;
            ones.pop();

            //debug(r, c);
            if (!decrease(r, c))
                return;

            nonZero--;
        }
    }

    reverse(ans.begin(), ans.end());
    for (pair<int, int> i : ans)
        debug(i.first, i.second);
}
/**
1 2
3 3
3 1
1 3
1 1
3 2
2 3
2 1
2 2

2 3 2
1 0 1
3 1 3
**/
int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}