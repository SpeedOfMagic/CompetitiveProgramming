/** MIT License Copyright (c) 2018 Vasilyev Daniil **/
/*
Statement:
Given starting and ending time, find amount of times such minute arrow goes through hour arrow.
For example, in time period [23:50; 01:06] in 00:00 and between 01:05 and 01:06
minute arrow points to the same place as hour arrow, and one second later it goes through,
as a result answer is 2.

Solution:
I want to write down all possible times in form "hh:mm" in array, such that in time period
["hh:mm" - 1 (one minute earlier) : "hh:mm"] minute arrow goes through hour arrow.

Then, I may process all times in (starting time; ending time], and if any time is in the array, then
increment answer.

Also it's needed to increment answer, when starting time == "00:00" or == "12:00" (corner cases).
*/
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
const string fileName = "watches";
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
int ans = 0;
str nxt(str s) {
    int h = (s[0] - '0') * 10 + s[1] - '0';
    int m = (s[3] - '0') * 10 + s[4] - '0';
    if (m == 59) {
        m = 0;
        h++;
    } else m++;

    if (h == 24)
        h = 0;

    str d = "";
    d += char(h / 10 + '0');
    d += char(h % 10 + '0');
    d += ":";
    d += char(m / 10 + '0');
    d += char(m % 10 + '0');

    return d;
}

void run() {
    str s1, s2;
    read(s1, s2);

    str whereIntersects[] = {"00:00", "01:06", "02:11", "03:17", "04:22", "05:28", "06:33", "07:39", "08:44", "09:50", "10:55",
                             "12:00", "13:06", "14:11", "15:17", "16:22", "17:28", "18:33", "19:39", "20:44", "21:50", "22:55"};

    if (s1 == "00:00" || s1 == "12:00")
        ans++;
    while(s1 != s2) {
        s1 = nxt(s1);

        for (str i : whereIntersects)
            if (i == s1)
                ans++;

    }

    put ans;
}

int32_t main() {srand(time(0));ios::sync_with_stdio(0);cin.tie(0);cout.tie(0);put setprecision(15);run();return 0;}