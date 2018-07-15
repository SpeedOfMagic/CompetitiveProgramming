#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1000000000;
typedef double db;
typedef pair<ll, ll> pii;
typedef pair<ll, ll> pll;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);


    double n, p, q;
    cin >> n >> p >> q;
    double be = (n+n/100*p);
    double g = n;
    for(int c=0; c<6; c++){
        g += (g/100*q);
    }
    if(g >= be)cout << 2;
    else cout << 1;
    return 0;
}
close