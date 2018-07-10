/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Solution:
0. Suppose people sit around the table with radius 1.
1. Since N people are evenly spaced, they make regular polygon.
2. Let's numerate every person in clockwise order, starting from 0.
3. Since it's regular polygon, then for every 4 people with distinct numbers aa, bb, cc, dd,
if |aa - bb| = |cc - dd|, then dist(aa, bb) = dist(cc, dd).
4. Because of 3, I can say that there are no more than |a - b| possible distances, for every a and b.
5. Since a, b < n and a != b, then there are no more than n - 1 possible distances.
6. I want for each distance calculate 2 values: distance itself, and amount of unordered pairs that make that distance.
7. If n is even, then there is always "opposite" point, => there are n / 2 unordered pairs of {point, opposite point}.
8. In other cases, each point included in 2 pairs for given distance, => amount of unordered pairs = n * 2 / 2 = n.
9. After that I sort all distances, and try to find such distance,
that amount of pairs with distance <= given = t. It can be easily done.
10. Then I say that for minimum radius, next distance should be = 2 * d,
and this distance = 2 * d for maximum radius.

11. How to find radius? In other words, 
there are 2 isosceles triangles: 1st one has sides 1, 1, distance; and 2nd one has sides ?, ?, 2 * d.
I want to find such ?, that those triangles become similiar. In other words: ? / 1 = 2 * d / distance; ? = 2 * d / distance.
12. By substituting distance I get minimum and maximum radiuses.
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
void run() {
    int n, d, t;
    read(n, d, t);

    double x[n], y[n];
    x[0] = 1; y[0] = 0;
    rep(i, 1, n) {
        x[i] = cos(2.0 * i * acos(-1.0) / double(n));
        y[i] = sin(2.0 * i * acos(-1.0) / double(n));
    }

    v<pair<double, int>> posDistances;

    rep(j, 1, n / 2 + 1)
        posDistances.pb({sqrt((x[0] - x[j]) * (x[0] - x[j]) + (y[0] - y[j]) * (y[0] - y[j])),
                            (n % 2 == 0 && j == n / 2 ? n / 2 : n)
                        });

    sort(posDistances.begin(), posDistances.end());

    //for (double i : posDistances) print(i); eol;
    int s = 0;
    int ind = 0;
    for (; ind < sz(posDistances); ind++) {
        if (s == t)
            break;

        s += posDistances[ind].second;
    }

    print((ind == sz(posDistances) ? 0 : 2.0 * double(d) / posDistances[ind].first), 2.0 * double(d) / posDistances[ind - 1].first);
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
