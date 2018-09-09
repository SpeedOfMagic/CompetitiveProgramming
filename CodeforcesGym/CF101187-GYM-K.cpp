#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const int inf = 1000000000;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    int kol_vo;
    cin >> kol_vo;
    for(int c=0; c<kol_vo; c++){
        ll a, n;
        cin >> a >> n;
        ll down =  a / n * n;
        ll up = down + n;
        cout << min(up ^ a, down ^ a) << endl;
    }
    return 0;
}