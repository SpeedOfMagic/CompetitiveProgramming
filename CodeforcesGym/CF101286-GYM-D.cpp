/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
An array a with n elements is given. Construct array b with n elements such that:
1. b[0] = 1
2. abs(b[i] - b[i - 1]) <= 1 for each i in [1 : n - 1]
3. if a[i] != 0, then b[i] <= a[i] for each i in [0 : n - 1].
4. ((1 / b[0]) + (1 / b[1]) + ... + (1 / b[n - 1])) is minimized.
Print ((1 / b[0]) + (1 / b[1]) + ... + (1 / b[n - 1])).

Solution:
The main idea is to go greedily through all segments, and increase whenever possible,
and at the end before next element a[i] > 0 decrease.
It can be done with careful implementation.

There may be cases where it's impossible to go from one a[i] to a[j] in given distance.
(for example, in [0, 0, 0, 0, 5, 0, 2] you can't make array b such b[5] = 5, because b[7] <= 2)
Then I want to change array a that it's always possible to do that.
It can be done by going from end to begin of array and always updating value to min(a[i], a[index] + distance(i, index)),
where a[index] != 0.
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
#if 1  //FileIO
const string fileName = "holes";
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
void run() {
    int n;
    get n;
    int a[n];
    rep(i, 0, n)
        get a[i];

    a[0] = 1;
    rep(i, 1, n)
        if (a[i] == 0)
            a[i] = inf;

    int pr = -1;
    for (int i = n - 1; i >= 0; i--)
        if (a[i] != inf) {
            if (pr == -1) {
                pr = i;
                continue;
            }
            int dist = pr - i;
            a[i] = min(a[i], a[pr] + dist);
            pr = i;
        }



    int speed[n];
    speed[0] = 1;
    pr = 0;
    rep(i, 1, n)
        if (a[i] != inf || i == n - 1) {

            rep(j, pr + 1, i + 1) {
                int dist = i - j + 1;
                //debug(i, j, dist, speed[j - 1], a[i]);
                if (speed[j - 1] - a[i] == dist)
                    speed[j] = speed[j - 1] - 1;
                else if (speed[j - 1] - a[i] > dist - 2)
                    speed[j] = speed[j - 1];
                else
                    speed[j] = speed[j - 1] + 1;
            }

            pr = i;
        }

    //for (int i : speed)print(i);eol;

    double ans = 0;
    for (int i : speed)
        ans += 1.0 / double(i);
    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
