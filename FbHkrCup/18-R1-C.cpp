/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: https://www.facebook.com/notes/facebook-hacker-cup/hacker-cup-2018-round-1-solutions/2267977239884831/
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

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        int n, m;
        read(n, m);
        int h[n];
        read(h[0], h[1]);
        int w, x, y, z;
        read(w, x, y, z);
        rep(i, 2, n)
            h[i] = (w * h[i - 2] + x * h[i - 1] + y) % z;

        rep(i, 0, n)
            h[i] *= 2;

        v<vint> event;
        rep(i, 0, m) {
            int a, b, u, d;
            read(a, b, u, d);
            u *= 2;
            d *= 2;
            if (a > b) {
                swap(a, b);
                swap(u, d);
            }

            event.pb(vint({a - 1, 0, u, d}));
            event.pb(vint({b - 1, 1, u, d}));
        }

        sort(event.begin(), event.end());

        int l = -1, r = inf;
        while (l + 1 < r) {
            map<int, int> u, d;
            int p = 0;
            int mid = (l + r) / 2;

            int pl = -1, pr = -1;
            rep(i, 0, n) {
                if (i == 0 || u.empty()) {
                    pl = max(h[i] - mid, 0ll);
                    pr = h[i] + mid;
                } else {
                    int mu = (*u.begin()).first, md = (*d.begin()).first;
                    pl = max(max(h[i] - mid, pl - md), 0ll);
                    pr = min(h[i] + mid, pr + mu);
                }
                //debug(mid, pl, pr);

                if (pl > pr) {
                    l = mid;
                    goto nxt;
                }

                while (p < sz(event) && event[p][0] == i) {
                    int cu = event[p][2], cd = event[p][3];
                    if (event[p][1] == 0) {
                        u[cu]++;
                        d[cd]++;
                    } else {
                        u[cu]--;
                        if (u[cu] == 0)
                            u.erase(cu);

                        d[cd]--;
                        if (d[cd] == 0)
                            d.erase(cd);
                    }

                    p++;
                }
            }
            r = mid;
            nxt:;
        }

        put "Case #" << test << ": " << r / 2 << "." << (r % 2) * 5 << endl;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
