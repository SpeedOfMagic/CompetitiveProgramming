/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/**
Statement: 
Rooted tree with only one vertex 1 is given.
Proccess q queries (1 <= q <= 500000):
ADD a b - Add vertex b to tree and attach it to a
GET v u - print LCA(v, u)
**/
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
const string fileName = "lca";
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
    
    int q;
    get q;
    

    const int N = 5e5 + 1;
    const int M = 20;
    int kthAncestor[N][M];
    int height[N];
    rep(i, 0, N)
        rep(j, 0, M)
            kthAncestor[i][j] = -1;

    height[1] = 0;

    for (; q; q--) {
        str query;
        get query;
        if (query == "ADD") {
            int a, b;
            read(a, b);
            height[b] = height[a] + 1;

            kthAncestor[b][0] = a;
            int p = a, k = 0;
            while (kthAncestor[p][k] != -1) {
                kthAncestor[b][k + 1] = kthAncestor[p][k];
                p = kthAncestor[p][k];
                k++;
            }
        } else {
            int v, u;
            read(v, u);
            if (height[v] > height[u])
                swap(v, u);
            int d = height[u] - height[v];
            int k = 0;
            while (d) {
                if (d & 1)
                    u = kthAncestor[u][k];
                k++;
                d >>= 1;
            }

            k = M - 1;
            while (v != u) {
                if (kthAncestor[v][k] != kthAncestor[u][k] || k == 0) {
                    v = kthAncestor[v][k];
                    u = kthAncestor[u][k];
                } else
                    k--;
            }

            put v << '\n';
        }
    }
}

int32_t main() {srand(time(0)); freopen("lca.in", "r", stdin);
    freopen("lca.out", "w", stdout);ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
close