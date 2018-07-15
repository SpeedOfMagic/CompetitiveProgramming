/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
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

void run() {
    int n, k;
    read(n, k);
    vint ans[n];
    int w[n];
    vint testsToPass[n];
    rep(i, 0, n) {
        get w[i];
        int c;
        get c;
        testsToPass[i] = vint(c);
        rep(j, 0, c) {
            get testsToPass[i][j];
            testsToPass[i][j]--;
        }
    }

    int s;
    get s;

    int testResults[s][k];
    vint facultiesToGo[s];
    set<int> facultiesToGoSet[s];

    rep(i, 0, s) {
        rep(j, 0, k)
            get testResults[i][j];

        int q;
        get q;
        rep(j, 0, q) {
            facultiesToGo[i].pb(getInt() - 1);
            facultiesToGoSet[i].insert(facultiesToGo[i].back());
        }
    }

    bool isStudent[s];
    rep(i, 0, s)
        isStudent[i] = 0;

    bool somebodyBecomeStudent = 1;
    while (somebodyBecomeStudent) {
        somebodyBecomeStudent = 0;

        v<pair<int, int>> resultForFaculty[n];
        rep(i, 0, n) {
            rep(j, 0, s) {
                if (isStudent[j])
                    continue;

                if (facultiesToGoSet[j].count(i)) {
                    int result = 0;
                    for (int l : testsToPass[i])
                        result += testResults[j][l];

                    resultForFaculty[i].pb({-result, j});
                }
            }
        }

        set<int> whereStudentCanGo[s];

        rep(i, 0, n) {
            sort(resultForFaculty[i].begin(), resultForFaculty[i].end());

            rep(j, 0, min(sz(resultForFaculty[i]), w[i] - sz(ans[i]))) {
                int studentId = resultForFaculty[i][j].second;
                whereStudentCanGo[studentId].insert(i);
            }
        }

        rep(i, 0, s) {
            if (whereStudentCanGo[i].empty())
                continue;

            for (int j : facultiesToGo[i]) {
                if (whereStudentCanGo[i].count(j)) {
                    ans[j].pb(i + 1);
                    somebodyBecomeStudent = 1;
                    isStudent[i] = 1;
                    break;
                }
            }
        }
    }

    for (vint i : ans) {
        print(sz(i));
        for (int j : i)
            print(j);
        eol;
    }
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}