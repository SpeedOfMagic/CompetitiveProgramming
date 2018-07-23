/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Solution is for ROI 2016, problem 6. The formal statement is almost the same, but instead of subsequence,
it must be subarrays. And n <= 3000, amount of queries <= 36000.

So, for each element p I want to find out, if it's value is among previous ones, or not.
It can be proven that amount of different costumes in subarray[l:r] >= amount in subarray[l+1:r],
then I can find right-most left pointer l such that value[l] = value[cur] by binary search:
Suppose mid points to some value. Then if (cur - l + 1) > amount of different costumes([l : cur]),
then ll = mid, otherwise rr = mid.
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
    int n;
    get n;
    int ans[n];
    ans[0] = 1;

    int p[n + 1];
    rep(i, 2, n + 1)
        p[i] = -1;
    p[1] = 0;

    map<int, int>inter;
    int z = 2;
    rep(i, 1, n) {
        v<pair<int, int>> tc;

        rep(j, 1, n + 1) {
            if(p[j] == -1)
                break;
            tc.push_back({p[j], j});
        }

        sort(tc.begin(), tc.end());
        int l = -1, r = sz(tc);
        while(l + 1 < r){
            int pos = (l + r) / 2;

            print(i - tc[pos].first + 1);
            rep(j, tc[pos].first + 1, i + 2)
                print(j);
            eol;

            int k;
            get k;

            int d;
            if(tc[pos].first + 1 > i - 1)
                d = 0;
            else
                d = inter[tc[pos].first * 3001 + 3001 + i - 1];

            k -= d;
            if(k == 1)
                l=pos;
            else
                r=pos;
        }
        if(l == -1)
            ans[i] = z++;
        else ans[i] = tc[l].second;

        p[ans[i]] = i;
        set<int> nw;
        for(int j = i; j >= 0; j--){
            nw.insert(ans[j]);
            inter[j * 3001 + i] = nw.size();
        }
    }
    print(0);
    for(int i : ans)
        print(i);
    eol;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
