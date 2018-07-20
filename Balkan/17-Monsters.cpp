/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
The idea is, I want to calculate for each cell in matrix the amount of submatrices it would erase.
For that, I may go through all possible contigous rows, and for each row I have 2 pointers,
which point to beginning and the end of valid submatrix. End pointer is always active,
and if current row is invalid, then left pointer moves. If current row is invalid,
then i send queries like "Add value x on segment[l; r] in column #i" and quickly process them later.
Yes, it shouldn't work (I guess), but after strange optimizations I got 937 ms processing time :).

The whole solution works in O(n^2 * m).
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
    int n = 750, m = 750;
    read(n, m);

    bool mat[n][m];
    rep(i, 0, n) {
        str s;
        get s;
        rep(j, 0, m)
            mat[i][j] = (s[j] - '0');
    }

    short preCols[n][m];
    rep(j, 0, m) {
        preCols[0][j] = mat[0][j];
        rep(i, 1, n)
            preCols[i][j] = preCols[i-1][j] + mat[i][j];
    }

    long long value[n + 1][m];
    rep(i, 0, n + 1)
        rep(j, 0, m)
            value[i][j] = 0;
    
    long long totDefence = 0;

    rep(l, 0, n)
        rep(r, l, n) {
            int ll = 0;
            rep(rr, 0, m)
                if (preCols[r][rr] - preCols[l][rr] + mat[l][rr] != r - l + 1) {
                    //debug(l, r, ll, rr, (rr - ll) * (rr - ll - 1) / 2 + (rr - ll));
                    
                    totDefence += (rr - ll) * (rr - ll - 1) / 2 + (rr - ll);
                    
                    int pr = 0;
                    for (int i = ll; i < rr; i++) {
                        int val = pr + ll + rr - i - i;//int val = (i - ll + 1) * (rr - i);
                        pr = val;
                        //debug(l, r, ll, rr, val);
                        value[l][i] += val;
                        value[r + 1][i] -= val;
                    }

                    ll = rr + 1;
                }
                
            int rr = m;
            totDefence += (rr - ll) * (rr - ll - 1) / 2 + (rr - ll);

            int pr = 0;
            for (int i = ll; i < rr; i++) {
                int val = pr + ll + rr - i - i;//int val = (i - ll + 1) * (rr - i);
                pr = val;
                //debug(l, r, ll, rr, val);
                value[l][i] += val;
                value[r + 1][i] -= val;
            }
        }

    rep(j, 0, m) {
        long long s = 0;
        rep(i, 0, n) {
            value[i][j] += s;
            s = value[i][j];
        }
    }

    long long mx = -1;
    rep(i, 0, n)
        rep(j, 0, m)
            if (mx < value[i][j])
                mx = value[i][j];

    put totDefence - mx;
    eol;

    //cerr << totDefence << " " << mx << endl;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
