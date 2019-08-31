/** MIT License Copyright (c) 2018-2019 Vasilev Daniil **/
/* Solution
Let's make trie based on a given dictionary. Then we need to find minimal amount of operations to visit every vertex in trie if we can move to neighbouring vertexes. This can be done greedily by laying a path to vertex with maximum height and then processing all vertexes that don't lie on this path first.
*/
#include <bits/stdc++.h>
using namespace std;
template<typename T> using v = vector<T>;
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
const long double EPS = 1e-11;
#if 0  //FileIO
const string fileName = "";
ifstream fin ((fileName == "" ? "input.txt"  : fileName + ".in" ));
ofstream fout((fileName == "" ? "output.txt" : fileName + ".out"));
#define get fin >>
#define put fout <<
#else
#define get cin >>
#define put cout <<
#endif
#define eol put endl
void read() {} template<typename Arg,typename... Args> void read (Arg& arg,Args&... args){get (arg)     ;read(args...) ;}
void print(){} template<typename Arg,typename... Args> void print(Arg  arg,Args...  args){put (arg)<<" ";print(args...);}
int getInt(){int a; get a; return a;}
mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
//code starts here
//2 11 6

struct trie {
	map<int, trie*> nxt;
	char c;
	int h = 0;
	int cnt = 0;

	trie(char C) {
		c = C;
	}
};

void findMax(trie *cur, int h) {
	cur -> h = h;
	for (auto i : cur -> nxt) {
		findMax(i.sc, h + 1);
		cur -> h = max(cur -> h, i.sc -> h);
	}
}

v<char> ans;
void makeAns(trie *cur, char hasLast) {
	if (cur -> cnt)
		ans.pb('P');
	//print(cur -> h); eol;
	int lastInd = -1;
	for (auto i : cur -> nxt) {
		if (hasLast && lastInd == -1 && cur -> h == i.sc -> h)
			lastInd = i.fs;
		else {
			ans.pb(i.sc -> c);
			makeAns(i.sc, 0);
			ans.pb('-');
		}
	}

	if (lastInd != -1) {
		ans.pb(cur -> nxt[lastInd] -> c);
		makeAns(cur -> nxt[lastInd], 1);
	}
}

void run() {
	int n;
	get n;

	trie* rt = new trie('-');
	rep(i, 0, n) {
		str s;
		get s;
		trie *cur = rt;
		rep(j, 0, sz(s)) {
			if (cur -> nxt[s[j] - 'a'] == nullptr)
				cur -> nxt[s[j] - 'a'] = new trie(s[j]);

			cur = cur -> nxt[s[j] - 'a'];
		}
		cur -> cnt++;
	}

	findMax(rt, 0);
	makeAns(rt, 1);
	put sz(ans);
	eol;
	for (char i : ans)
		put i << "\n";
}

signed main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); put fixed << setprecision(12); run();}
