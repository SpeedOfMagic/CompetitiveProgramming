#include <bits/stdc++.h>
#define sz(a) (int) a.size()
using namespace std;

int main()
{
    int n, m, k;
    cin >> n >> m >> k;
    vector<vector<int>> ev;
    int B[k];
    for (int i = 0; i < k; i++) {
        int a, b;
        cin >> a >> b;
        ev.push_back({a, 1, i});
        ev.push_back({b, 0, i});
        B[i] = b;
    }
    sort(ev.begin(), ev.end());
    set<int> canSeat, canStand;
    for (int i = 1; i <= m; i++) {
        canSeat.insert(i);
        canStand.insert(i);
    }
    canSeat.erase(m);

    int seating[k], standing[k];
    int time[m + 1];
    for (int i = 1; i <= m; i++)
        time[i] = 0;
    memset(seating, 0, sizeof(seating));
    memset(standing, 0, sizeof(standing));
    for (int i = 0; i < sz(ev); i++) {
        if (ev[i][1]) {
            if (canSeat.empty()) {
                if (!canStand.empty()) {
                    int d = *canStand.begin();
                    canStand.erase(d);
                    standing[ev[i][2]] = d;
                    time[d] += B[ev[i][2]] - ev[i][0];
                }
            } else {
                int d = *canSeat.begin();
                canSeat.erase(d);
                seating[ev[i][2]] = d;
            }
        } else {
            if (seating[ev[i][2]] == 0) {
                if (standing[ev[i][2]])
                    canStand.insert(standing[ev[i][2]]);
            } else
                canSeat.insert(seating[ev[i][2]]);
        }
    }
    int ind = 1;
    for (int i = 2; i <= m; i++)
        if (time[i] < time[ind])
            ind = i;
    cout << time[ind] << " " << ind;
    return 0;
}