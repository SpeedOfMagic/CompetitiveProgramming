/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
#define check(a) put #a << ": " << a << endl;
void read() {}     template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){}     template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
void debug(){eol;} template<typename Arg,typename... Args> void debug(Arg  arg,Args...  args){put (arg)<<" ";debug(args...);}
int getInt(){int a; get a; return a;}
//code goes here

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        put "Case " << test << ": ";
        int n, k;
        read(n, k);
        pair<int, int> arr[n];
        rep(i, 0, n)
            read(arr[i].first, arr[i].second);
        sort(arr, arr + n, [](auto a, auto b) {return a.second < b.second;});

        map<int, int> d;
        rep(i, 0, n)
            d[arr[i].first]++;

        rep(i, 0, k - 1) {
            int v = (*d.begin()).first;
            d[v]--;
            if (d[v] == 0)
                d.erase(v);
        }


        int ans = inf;
        int p = 0;
        int tot = n;
        rep(l, 0, n) {
            if (tot < k)
                break;

            int st = arr[l].second;
            int en = (*d.begin()).first;
            ans = min(ans, en - st);
            if (l + 1 < n && arr[l].second != arr[l + 1].second) {
                for (; p <= l; p++) {
                    int v = max((*d.begin()).first, arr[p].first);
                    d[v]--;
                    if (d[v] == 0)
                        d.erase(v);
                    tot--;
                }
            }
        }

        put max(ans, 0ll);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
close