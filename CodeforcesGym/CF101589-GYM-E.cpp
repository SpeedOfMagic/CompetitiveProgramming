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


    int girls, boys;
    cin >> boys >> girls;
    int kol_vo;
    cin >> kol_vo;
    vector<int> v(kol_vo);
    for(int c=0; c<kol_vo; c++)
        cin >> v[c];
    int all = girls;
    vector<pair<int, int> > dop;
    for(int c=0; c<kol_vo; c++){
        int an1=0, an2=0;
        if(v[c] == all){
            dop.push_back({0, 0});
            continue;
        }
        if(v[c] < all){
            an2 += (all-v[c]);
            girls -= (all-v[c]);
            all = v[c];
        }
        else {
            an1 += (v[c]-all);
            boys -= (v[c]-all);
            all = v[c];
        }
        dop.push_back({an1, an2});
    }
    if(girls < 0 || boys < 0){
        cout << "ERROR";
        return 0;
    }
    for(int c=0; c<dop.size(); c++)
        cout << dop[c].first << " " << dop[c].second << endl;
    return 0;
}