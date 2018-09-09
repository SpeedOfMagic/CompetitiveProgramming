#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1000000000;
const ll LIM = 1e7 + 1;
const ll NEED = 100;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    ll x;
    cin >> x;
    if (x <= LIM) {
        for (ll i = x; i <= x + x / 100; i++) {
            ll res = 0;
            for (ll j = 1; j <= ceil(sqrt(i)); j++)
                if (i % j == 0)
                    res += 1 + (j * j != i);
            if (res >= NEED) {
                cout << i << endl;
                cerr << res << endl;
                return 0;
            }
        }
        cout << -1 << endl;
    } else {//5 * 2 * 5 * 2
        ll d = 45360 * (x / 45360);
        while (d <= x)
            d += 45360;
        cout << d << endl;
    }
    return 0;
}