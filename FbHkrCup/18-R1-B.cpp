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
vint a, b;
vint preorder, postorder;
vint belongInPreorder, belongInPostorder;

void makePreorder(int cur = 1) {
    if (cur == 0)
        return;

    belongInPreorder[cur] = sz(preorder);
    preorder.pb(cur);

    makePreorder(a[cur]);
    makePreorder(b[cur]);
}

void makePostorder(int cur = 1) {
    if (cur == 0)
        return;

    makePostorder(a[cur]);
    makePostorder(b[cur]);

    belongInPostorder[cur] = sz(postorder);
    postorder.pb(cur);
}

void run() {
    int t;
    get t;
    for (int test = 1; test <= t; test++) {
        int n, k;
        read(n, k);
        n++;
        a = vint(n);
        b = vint(n);
        preorder = vint({-1});
        postorder = vint({-1});
        belongInPreorder = vint(n);
        belongInPostorder = vint(n);

        rep(i, 1, n)
            read(a[i], b[i]);

        makePreorder();
        makePostorder();

        int ans[n];
        rep(i, 1, n)
            ans[i] = -1;

        int cur = 0;
        rep(i, 1, n) {
            if (ans[i] == -1) {
                ans[i] = cur % k;

                int currentInPreorder = preorder[i], currentInPostorder = postorder[i];
                while (currentInPostorder != -1 || currentInPreorder != -1) {
                    if (currentInPostorder != -1) {
                        currentInPostorder = belongInPreorder[currentInPostorder];
                        if (ans[currentInPostorder] != -1)
                            currentInPostorder = -1;
                        else
                            ans[currentInPostorder] = cur % k;
                        if (currentInPostorder != -1)
                            currentInPostorder = postorder[currentInPostorder];
                    }

                    if (currentInPreorder != -1) {
                        currentInPreorder = belongInPostorder[currentInPreorder];
                        if (ans[currentInPreorder] != -1)
                            currentInPreorder = -1;
                        else
                            ans[currentInPreorder] = cur % k;
                        if (currentInPreorder != -1)
                            currentInPreorder = preorder[currentInPreorder];
                    }
                }
                cur++;
            }
        }

        put "Case #" << test << ": ";
        if (cur >= k) {
            rep(i, 1, n - 1)
                print(ans[belongInPreorder[i]] + 1);
            put ans[belongInPreorder[n - 1]] + 1 << endl;
        } else
            put "Impossible" << endl;

    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
