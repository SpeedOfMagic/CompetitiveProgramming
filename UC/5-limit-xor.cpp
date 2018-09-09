/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
#pragma GCC optimize("Ofast")
template<typename T> using v = vector<T>;
template<typename T, typename U>  using hmap = __gnu_pbds::gp_hash_table<T, U>;
#define int long long
typedef long double ld;
typedef string str;
typedef vector<int> vint;
#define rep(a, l, r) for(int a = (l); a < (r); a++)
#define pb push_back
#define fs first
#define sc second
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
struct trie{
    int size = 0;
    bool end = 0;
    trie* nxt[2] = {nullptr, nullptr};

    trie() {}
};

int size(trie* cur) {
    if (cur == nullptr)
        return 0;
    else
        return cur -> size;
}

void add(str s, trie* root){
    trie* cur = root;
    cur -> size++;

    for (char i : s) {
        if(cur -> nxt[i - '0'] == nullptr)
            cur -> nxt[i - '0'] = new trie();
        cur = cur -> nxt[i - '0'];
        cur -> size++;
    }

    cur -> end = 1;
}

const unsigned int requiredLength = 30;

string inttobinary(int a) {
    string res = "";

    if (a == 0)
        res = "0";

    for (int d = a; d > 0; d >>= 1){
        if ((d & 1) == 1)
            res += "1";
        else
            res += "0";
    }

    while (res.length() < requiredLength)
        res += "0";

    reverse(res.begin(), res.end());
    return res;
}

int msb(int i) {
    i |= (i >>  1);
    i |= (i >>  2);
    i |= (i >>  4);
    i |= (i >>  8);
    i |= (i >> 16);
    return i - ((unsigned)i >> 1);
}

void run() {
    int n, k;
    read(n, k);
    int a[n];
    rep(i, 0, n)
        get a[i];
    int s = 0;
    trie* root = new trie();
    int ans = 0;
    rep(i, 0, n) {
        add(inttobinary(s), root);
        s ^= a[i];

        trie* cur = root;
        int val = (1 << 29);
        while (size(cur)) {
            if (s & val) {
                if (val & k) {
                    ans += size(cur -> nxt[1]);
                    cur = cur -> nxt[0];
                } else
                    cur = cur -> nxt[1];
            } else {
                if (val & k) {
                    ans += size(cur -> nxt[0]);
                    cur = cur -> nxt[1];
                } else 
                    cur = cur -> nxt[0];
            }
            val /= 2;
        }
    }

    put ans;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
