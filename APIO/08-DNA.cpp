/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
//Used similiar approach: https://github.com/Yehezkiel01/CompetitiveProgramming/blob/master/APIO/APIO-08-DNA.cpp
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

void run() {
    int m, K, r;
    read(m, K, r);
    str s;
    get s;

    map<char, int> dna;
    dna['A'] = 0;
    dna['C'] = 1;
    dna['G'] = 2;
    dna['T'] = 3;
    char dnaInv[4] = {'A', 'C', 'G', 'T'};

    int dp[m][K + 1][4];
    rep(i, 0, m)
         rep(j, 0, K + 1)
            rep(k, 0, 4)
                dp[i][j][k] = 0;

    if (s[m - 1] == 'N')
        rep(i, 0, 4)
            dp[m - 1][1][i] = 1;
    else
        dp[m - 1][1][dna[s[m - 1]]] = 1;

    for (int i = m - 2; i >= 0; i--)
        rep(j, 1, K + 1)
            rep(k, 0, 4) {
                if (s[i] != 'N')
                    k = dna[s[i]];

                rep(l, 0, 4)
                    if (k > l) {
                        if (j > 1)
                            dp[i][j][k] += dp[i + 1][j - 1][l];
                    } else
                        dp[i][j][k] += dp[i + 1][j][l];

                if (s[i] != 'N')
                    break;
            }

    int curForm = 1;
    for (int i = 0; i < m; i++) {
        //debug(i, r, curForm);
        if (s[i] == 'N') {
            rep(j, 0, 4) {
                int posForm = curForm;
                if (i == 0 || dna[s[i - 1]] <= j)
                    posForm--;

                int posCombinations = 0;
                rep(k, 1, K + 1) {
                    if (posForm + k > K)
                        break;

                    posCombinations += dp[i][k][j];
                }

                //debug(i, j, r, posCombinations);
                if (posCombinations < r)
                    r -= posCombinations;
                else {
                    s[i] = dnaInv[j];
                    break;
                }
            }
        }

        if (i && s[i - 1] > s[i])
            curForm++;
    }

    put s;
}

int32_t main() {srand(time(0)); ios::sync_with_stdio(0); cin.tie(0); cout.tie(0); put fixed; put setprecision(15); run(); return 0;}
