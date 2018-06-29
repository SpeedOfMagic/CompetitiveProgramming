/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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
int getRandom(int limit) { //returns random value in half-interval [0; limit);
    //don't forget to write srand(time(0));
    return ((rand() << 16) + rand()) % limit;
}

struct waveletTree{
    waveletTree *left = nullptr, *right = nullptr;
    int l, r;
    vector<unsigned int> mapLeftVector;

    unsigned int mapLeft(int i) {
        return mapLeftVector[i];
    }

    unsigned int mapRight(int i) {
        return i - mapLeftVector[i] + 1;
    }

    waveletTree(int ll, int rr): l(ll), r(rr) {}
};

waveletTree* root;

void init(waveletTree* nodeToInit, vector<int>& sequence) {
    int mn = nodeToInit -> l, mx = nodeToInit -> r;

    if (mn != mx) { //this also means that current node is not a leaf
        int middle = (mn + mx) / 2;
        if (middle == mx)
            middle--;

        nodeToInit -> left = new waveletTree(mx, mn);
        nodeToInit -> right = new waveletTree(mx, mn);

        vector<int> sequenceLeft;
        vector<int> sequenceRight;
        for(int i : sequence) {
            if (i <= middle) {
                sequenceLeft.push_back(i);
                nodeToInit -> left -> l = min(nodeToInit -> left -> l, i);
                nodeToInit -> left -> r = max(nodeToInit -> left -> r, i);
            } else {
                sequenceRight.push_back(i);
                nodeToInit -> right -> l = min(nodeToInit -> right -> l, i);
                nodeToInit -> right -> r = max(nodeToInit -> right -> r, i);
            }
            nodeToInit -> mapLeftVector.push_back(sequenceLeft.size());
        }

        init(nodeToInit -> left, sequenceLeft);
        init(nodeToInit -> right, sequenceRight);
    }

}

waveletTree* init(vector<int>& sequence) {
    if (sequence.empty())
        return nullptr;

    int mn = *min_element(sequence.begin(), sequence.end());
    int mx = *max_element(sequence.begin(), sequence.end());

    waveletTree* nodeToInit = new waveletTree(mn, mx);

    init(nodeToInit, sequence);

    return nodeToInit;
}

int equalTo(int q, int l, int r, waveletTree* cur = root) {
    if (l != 1)
        return equalTo(q, 1, r) - equalTo(q, 1, l - 1);

    if (cur -> l == cur -> r || r == 0) //this condition checks if current node is a leaf
        return r;

    int middle = cur -> left -> r;

    if (q <= middle)
        return equalTo(q, l, cur -> mapLeft(r - 1), cur -> left);
    else
        return equalTo(q, l, cur -> mapRight(r - 1), cur ->right);
}

int lessThan(int q, int l, int r, waveletTree* cur = root) {
    if(l != 1)
        return lessThan(q, 1, r) - lessThan(q, 1, l-1);

    if (cur -> l == cur -> r || r == 0) //this condition checks if current node is a leaf
        return 0;

    int middle = cur -> left -> r;

    if (q <= middle)
        return lessThan(q, l, cur -> mapLeft(r - 1), cur -> left);
    else
        return cur -> mapLeft(r - 1)+ lessThan(q, l, cur -> mapRight(r - 1), cur -> right);
}

int lsb(int pos) {
    return pos & -pos;
}

struct fenwick {
    v<long long> fenwickTree;

    void update(int p, int x) {
        while (p <= sz(fenwickTree)) {
            fenwickTree[p - 1] += x;
            p += lsb(p);
        }
    }

    long long query(int l, int r) {
        if (r == 0)
            return 0;

        if (l != 1)
            return query(1, r) - query(1, l - 1);

        return query(1, r - lsb(r)) + fenwickTree[r - 1];
    }

    fenwick(vint sequence) {
        while (sz(sequence) & (sz(sequence) - 1))
            sequence.pb(0);

        vint pre = sequence;
        rep(i, 1, sz(pre))
            pre[i] += pre[i - 1];

        rep(i, 0, sz(sequence)) {
            int l = lsb(i + 1) - 1;
            fenwickTree.pb(pre[i] - pre[i - l] + sequence[i - l]);
        }


    }
};


void run() {
    int n;
    get n;

    vint a(n);
    rep(i, 0, n)
        get a[i];

    int b[n];
    rep(i, 0, n)
        b[i] = a[i];
    sort(b, b + n);

    map<int, int> d;
    rep(i, 0, n)
        d[b[i]] = i;

    rep(i, 0, n)
        a[i] = d[a[i]];

    root = init(a);

    vint moreThan(n);
    moreThan[0] = 0;
    rep(i, 1, n)
        moreThan[i] = i - equalTo(a[i], 1, i) - lessThan(a[i], 1, i);


    fenwick* fenwickTree = new fenwick(vint(n, 0));
    long long ans = 0;
    rep(i, 0, n) {
        int p = a[i];
        ans += fenwickTree -> query(p + 1, n);
        fenwickTree -> update(p + 1, moreThan[i]);
        //debug(i, p, moreThan[i]);
    }
    put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}