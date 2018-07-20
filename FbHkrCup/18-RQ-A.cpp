/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Idea is, let's make simple implementation of visiting attractions,
until Alex visits the same attraction twice.
Then, I say that Alex will go by the same cycle again.
Suppose that length of cycle = m, then after m, m * 2, m * 3 ... visits Alex go to the
same place, => after v % m visits she'll be in the same place again.
After that, it's easy to implement resulting part, since m <= n, => v % m < 50.
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
int n, k;

str makeAnswer(queue<str> attractions, queue<int> numbers) {
    pair<int, str> pos[k];

    str res = "";
    rep(i, 0, k) {
        pos[i] = {numbers.front(), attractions.front()};
        attractions.pop();
        numbers.pop();
    }

    sort(pos, pos + k);
    rep(i, 0, k)
        res += pos[i].second + " ";

    res.pop_back();
    return res;
}

str solveTouristStupid(int v, queue<str> attractions, queue<int> numbers) {
    while(v - 1) {
        rep(i, 0, k) {
            attractions.push(attractions.front());
            attractions.pop();

            numbers.push(numbers.front());
            numbers.pop();
        }

        v--;
    }

    return makeAnswer(attractions, numbers);
}

str solveTourist(int v, queue<str> attractions, queue<int> numbers) {
    int cycle = 0;
    int ind = 0;

    bool vis[n];
    rep(i, 0, n)
        vis[i] = 0;

    while(!vis[ind]) {
        vis[ind] = 1;
        ind = (ind + k) % n;
        cycle++;
    }

    v %= cycle;
    v += cycle;

    return solveTouristStupid(v, attractions, numbers);
}



void run() {
    int t;
    get t;
    rep(test, 1, t + 1) {
        int v;
        read(n, k, v);

        queue<str> attractions;
        queue<int> numbers;
        rep(i, 0, n) {
            str s;
            get s;
            attractions.push(s);
            numbers.push(i);
        }

        str ans = solveTourist(v, attractions, numbers);

        put "Case #" << test << ": " << ans;
        eol;
    }
}

int32_t main() {srand(time(0)); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
