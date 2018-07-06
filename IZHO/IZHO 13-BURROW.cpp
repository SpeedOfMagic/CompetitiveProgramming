/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
It's obvious that if it's possible to find submatrix with area k and minimum p,
then it's also possible to find submatrix with area k and minimum < p.
That means it's possible to make binary search for solution.

For that, let's take all elements of matrix, sort them, and I'm going to search first index j such 
it's impossible to find submatrix with area k and minimum allElements[j - 1].

Since if element is less than value, which is processed in binary search, then I want to say that I can't access that element.
So, let's make binary matrix, where 0 means "can't access", and 1 means "can access". And It'll end up with
"Find maximum rectangle area in given matrix, such that every element in rectangle is 1".

Solution for that is described in CSES-Building.cpp

After that, if maximum area < k, then it's impossible to get maximum of given value, => r -> (l + r) / 2.
Otherwise, l -> (l + r) / 2.

Time complexity: O(nm log(nm)).
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
    int t;
    get t;
    for (; t; t--) {
        int n, m, k;
        read(n, m, k);

        vint allElements;

        int mat[n][m];
        rep(i, 0, n)
            rep(j, 0, m) {
                get mat[i][j];
                allElements.push_back(mat[i][j]);
            }

        sort(allElements.begin(), allElements.end());
        int l = -1;
        int r = unique(allElements.begin(), allElements.end()) - allElements.begin();

        int ans1 = 0, ans2 = 0;

        while (l + 1 < r) {
            int val = allElements[(l + r) / 2];
            int curSeg[m];
            rep(i, 0, m)
                curSeg[i] = 0;

            int area = 0;

            rep(i, 0, n) {
                rep(j, 0, m)
                    if (mat[i][j] >= val)
                        curSeg[j]++;
                    else
                        curSeg[j] = 0;

                stack<int> index;
                int indexLowerLeft[m];
                rep(j, 0, m) {
                    while (!index.empty() && curSeg[index.top()] >= curSeg[j])
                        index.pop();

                    if (!index.empty())
                        indexLowerLeft[j] = index.top();
                    else
                        indexLowerLeft[j] = -1;

                    index.push(j);
                }

                int indexLowerRight[m];
                index = stack<int>();

                for (int j = m - 1; j >= 0; j--) {
                    while (!index.empty() && curSeg[index.top()] >= curSeg[j])
                        index.pop();

                    if (!index.empty())
                        indexLowerRight[j] = index.top();
                    else
                        indexLowerRight[j] = m;

                    index.push(j);
                }

                rep(j, 0, m) {
                    int ll = indexLowerLeft[j] + 1;
                    int rr = indexLowerRight[j] - 1;
                    //debug(i, j, l, r, curSeg[j]);
                    area = max(area, (rr - ll + 1) * curSeg[j]);
                }
            }

            if (area >= k) {
                l = (l + r) / 2;

                if (ans1 < val)
                    ans1 = val, ans2 = area;
            } else
                r = (l + r) / 2;
        }

        print(ans1, ans2);
        eol;
    }

}
/**
1 1
**/
int32_t main() {srand(time(0));cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}
