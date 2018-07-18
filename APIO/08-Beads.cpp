/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
/*
My solution's idea heavily relies on solution from IOI 2014 practice - Questions I ask myself.

For every bead there are 2 arrays: 1st one tells the number of swapper that changes bead's position,
and another array tells where bead will go.
It can be easily constructed by simple implementation of the whole process.

When query appears, I can look at the array, and find 1st number which is <= J, and get its index.
then get the value from another array, with the index I got earlier. That will be the answer.
There is 1 corner case, when there is no such number. Then, answer is K since bead hasn't moved.

Time complexity: O(n + q * log m)
Memory complexity: O(n + m)
*/
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
    int n, m;
    read(n, m);
    n++;
    vint swapperNum[n], willBePosition[n];

    int currentPosition[n];
    rep(i, 1, n)
        currentPosition[i] = i;

    for (int i = 0; i < m; i++) {
        int p;
        get p;

        int first = currentPosition[p], second = currentPosition[p + 1];

        swapperNum[first].pb(i + 1);
        swapperNum[second].pb(i + 1);

        willBePosition[first].pb(p + 1);
        willBePosition[second].pb(p);

        swap(currentPosition[p], currentPosition[p + 1]);
    }

    put "getNumQuestions";
    eol;

    int q;
    get q;
    for (; q; q--) {
        put "getQuestion";
        eol;

        int k, j;
        read(k, j);

        int ans = k;
        int ind = upper_bound(swapperNum[k].begin(), swapperNum[k].end(), j) - swapperNum[k].begin();
        if (ind) {
            ind--;
            ans = willBePosition[k][ind];
        }

        put "answer " << ans;
        eol;
    }
}

int32_t main() {srand(time(0));cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
