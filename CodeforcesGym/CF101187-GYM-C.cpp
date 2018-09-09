#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
const ll inf = 1000000000;

ll kol_vo, k, m;
vector<ll> pos;

void init(){
    pos = vector<ll>(m, 0);
}

vector<ll> f(){
    vector<ll> dp(m+1);
    dp[0] = max(pos[0]-k, 0ll);
    for(ll c=1; c<=m; c++){
        ll pos_prev1 = pos[c-1] - k;
        ll pos_prev = lower_bound(pos.begin(), pos.end(), pos_prev1)-pos.begin();
        if(pos_prev1 != pos[pos_prev])pos_prev--;
        if(pos_prev < 0)dp[c] = max(pos_prev1, 0ll);
        else {
            dp[c] = dp[pos_prev+1] + (pos_prev1 - pos[pos_prev]);
        }
    }
    return dp;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);

    cin >> kol_vo >> k >> m;
    init();
    for(ll c=0; c<m; c++)
        cin >> pos[c];
    sort(pos.begin(), pos.end());
    vector<ll> mmin1 = f();
    vector<ll> pos_beg = pos;
    for(ll c=0; c<pos.size(); c++){
        pos[c] = (kol_vo - pos[c]+1);
    }
    sort(pos.begin(), pos.end());
    vector<ll> mmin2 = f();
    reverse(mmin2.begin(), mmin2.end());
    ll answ = 0, otv=0;
    /*for(ll c=0; c<=m; c++)
        cout << mmin1[c] << " ";
    cout << endl;
    for(ll c=0; c<=m; c++)
        cout << mmin2[c] << " ";*/
    for(ll c=0; c<=m; c++){
        answ = 0;
        if(c == 0){
            answ = mmin2[c+1];
            answ += pos_beg[0]-1;
            otv = max(answ, otv);
            continue;
        }
        if(c == m){
            answ = mmin1[c];
            answ += kol_vo - pos_beg[m-1];
            otv = max(answ, otv);
            continue;
        }
        answ = max(answ, mmin1[c] + mmin2[c]);
        answ += pos_beg[c] - pos_beg[c-1]-1;
        otv = max(answ, otv);
    }
    cout << otv;
    return 0;
}
close