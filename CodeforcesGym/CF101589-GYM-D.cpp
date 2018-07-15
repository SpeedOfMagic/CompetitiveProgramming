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

void run() {
    int n, m;
    read(n, m);
    str mp[n];
    int r = -1, c = -1;
    rep(i, 0, n) {
        get mp[i];
        rep(j, 0, m) {
            if (mp[i][j] == 'P') {
                r = i;
                c = j;
            }
        }
    }

    while (r < n) {
        if (mp[r][c] == '.' || mp[r][c] == 'P')
            r++;
        else {
            if (mp[r][c] == '\\') {
                if (c + 1 == m || mp[r][c + 1] == '/') {
                    put -1;
                    return;
                } else {
                    r++;
                    c++;
                }
            } else {
                if (c == 0 || mp[r][c - 1] == '\\') {
                    put -1;
                    return;
                } else {
                    r++;
                    c--;
                }
            }
        }
    }

    put c + 1;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
close