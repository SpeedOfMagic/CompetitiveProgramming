/* Solution
Let f(x) = {(x + x / b) % a, x % b}
It's possible to prove that this f(x) is periodic with period = ab / gcd(a, b + 1)
Then you need for each segment calculate part of periodic cycle they cover, then find 1-2 segments that cover the same part, but their right bounds must be less than a period of f(x).
The answer is a size of a union of such segments
Also it's needed to check if a * b can overflow and if one of segments has length >= period
*/
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
signed main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n, a, b;
    cin >> n >> a >> b;
    a /= __gcd(a, b + 1);
    vector<pair<ll, ll>> seg;
    ll mod = 1000000000000000001; //maximum possible answer
    if (a <= 9223372036854775807 / b) /* a * b can overflow */;
        mod = a * b;
    for (int i = 0; i < n; i++) {
        ll l, r;
        cin >> l >> r;
        if (r - l + 1 >= mod) {
            cout << mod << endl;
            return 0;
        }
        ll ll = l % mod, rr = r % mod;
        if (ll <= rr)
            seg.push_back({ll, rr});
        else {
            seg.push_back({ll, mod - 1});
            seg.push_back({0, rr});
        }
    }
	
    sort(seg.begin(), seg.end());
    ll ans = 0;
    ll l = seg[0].first, r = seg[0].second;
    for (pair<ll, ll> i : seg)
        if (r < i.first) {
            ans += r - l + 1;
            l = i.first;
            r = i.second;
        } else
            r = max(r, i.second);
    ans += r - l + 1;
    cout << ans;
    return 0;
}