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


    int need;
    cin >> need;
    need = 1000 - need;
    vector<int> v(6);
    for(int c=0; c<6; c++)
        cin >> v[c];
    vector<int> dop(6);
    dop[0] = 100;
    dop[1] = 50;
    dop[2] = 20;
    dop[3] = 10;
    dop[4] = 5;
    dop[5] = 1;
    int kol = 0;
    for(int c=0; c<6; c++){
        while(v[c] && need >= dop[c]){
            kol++;
            need -= dop[c];
            v[c]--;
        }
    }
    if(need > 0){
        cout << "No solution";
        return 0;
    }
    cout << kol;
    return 0;
}