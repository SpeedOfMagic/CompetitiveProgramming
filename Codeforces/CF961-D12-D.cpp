/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Editorial: http://codeforces.com/blog/entry/58743
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
struct vt{
    int x, y;
    int operator* (vt other) {return this -> x * other.x + this -> y * other.y;}
    int operator% (vt other) {return this -> x * other.y - this -> y * other.x;}
    bool collinear(vt other) {return (*this) % other == 0;}
    vt(int x1, int y1, int x2, int y2) : x(x2 - x1), y(y2 - y1) {}
    vt() {}
};
void run() {
    int n;
    get n;

    int x[n], y[n];
    rep(i, 0, n)
        read(x[i], y[i]);

    if (n < 5) {
        put "YES";
        return;
    }

    vt possibleLine = vt(x[0], y[0], x[1], y[1]);

    int twoLinesNeeded = -1;

    rep(i, 2, n) {
        vt other = vt(x[0], y[0], x[i], y[i]);
        if (!other.collinear(possibleLine)) {
            twoLinesNeeded = i;
            break;
        }
    }

    if (twoLinesNeeded != -1) {
        int z = twoLinesNeeded;
        vt firstLine[3] = {vt(x[0], y[0], x[1], y[1]), vt(x[0], y[0], x[1], y[1]), vt(x[0], y[0], x[z], y[z])};
        vt secondLine[3]= {vt(x[0], y[0], x[z], y[z]), vt(x[1], y[1], x[z], y[z]), vt(x[1], y[1], x[z], y[z])};

        bool mayUse[3] = {1, 1, 1};
        int from[3] = {0, 1, z};

        vint dangerousPoints = vint({0, 1, z});

        rep(i, 2, n) {
            bool dangerous = 0;
            rep(j, 0, 3) {
                if (mayUse[j] == 0)
                    continue;

                vt toCheck = vt(x[from[j]], y[from[j]], x[i], y[i]);
                if (firstLine[j].collinear(toCheck) || secondLine[j].collinear(toCheck))
                    continue;
                else {
                    mayUse[j] = 0;
                    dangerous = 1;
                }
            }

            if (dangerous)
                dangerousPoints.pb(i);
        }

        if (mayUse[0] || mayUse[1] || mayUse[2])
            put "YES";
        else {
            for (int i : dangerousPoints)
                for (int j : dangerousPoints) {
                    if (i == j)
                        continue;

                    vt lineFirst = vt(x[i], y[i], x[j], y[j]);
                    int startLineSecond = -1;
                    vt lineSecond;
                    bool init = 0;

                    rep(k, 0, n) {
                        vt pos = vt(x[i], y[i], x[k], y[k]);
                        vt pos2;
                        if (init)
                            pos2 = vt(x[startLineSecond], y[startLineSecond], x[k], y[k]);

                        if (pos.collinear(lineFirst))
                            continue;
                        else if (init && lineSecond.collinear(pos2))
                            continue;
                        else if (init)
                            goto nxt;
                        else if (startLineSecond != -1) {
                            lineSecond = vt(x[startLineSecond], y[startLineSecond], x[k], y[k]);
                            init = 1;
                        } else
                            startLineSecond = k;
                    }

                    put "YES";
                    return;

                    nxt:;
                }

            put "NO";
        }
    } else
        put "YES";
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
