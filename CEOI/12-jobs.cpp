/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Since there is a strict ML, and values in the array are not sorted,
it's needed to keep them, and only them, without any other arrays.
Also, the whole problem may be divided into 2 parts:
1. Calculate the first line of output. It can be done by binary search.

2. Constructing the whole solution:
Firstly, it's needed to keep indices of values in any way (I used query datastructure).
Secondly, it may be easily printed by making simple implementation with 2 pointers.
*/
#include <bits/stdc++.h>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
//#define int long long
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
    int n, d, m;
    read(n, d, m);
    n++;

    queue<int> a[n];

    rep(i, 0, m) {
        int k;
        get k;
        a[k].push(i + 1);
    }

    int l = 0, r = m + 1;

    while (l + 1 < r) {
        int p = (l + r) / 2;
        int ll = 1;
        int leftToFinish = sz(a[ll]);

        rep(rr, 1, n + 1) {
            if (ll + d < rr) {
                l = p;
                goto nxt;
            }

            if (rr == n)
                break;

            int canDo = p;
            while(ll <= rr) {
                while (ll <= rr && leftToFinish == 0) {
                    ll++;
                    leftToFinish = sz(a[ll]);
                }

                if (canDo == 0 || ll > rr)
                    break;

                int z = min(canDo, leftToFinish);
                canDo -= z;
                leftToFinish -= z;
            }
        }
        r = p;
        nxt:;
    }

    int p = r;
    put p;
    eol;

    int ll = 1;
    rep(rr, 1, n) {
        int canDo = p;
        while(ll <= rr) {
            while (ll <= rr && a[ll].empty())
                ll++;

            if (canDo == 0 || ll > rr)
                break;

            int z = min(canDo, sz(a[ll]));
            canDo -= z;
            while(z) {
                print(a[ll].front());
                a[ll].pop();
                z--;
            }
        }
        put 0;
        eol;
    }
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
