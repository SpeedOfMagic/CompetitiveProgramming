#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int) a.size()
#define pb push_back
typedef long long ll;
typedef vector<int> vint;

int main()
{
    int h, w, n;
    cin >> h >> w >> n;

    string query;
    cin >> query;

    ll ax[n], bx[n], cx[n], dx[n];

    int k;

    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> ax[i];
    for (int i = k; i < n; i++)
        ax[i] = (10007 * ax[i - 2] + 10009 * ax[i - 1] + 87277) % h;

    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> bx[i];
    for (int i = k; i < n; i++)
        bx[i] = (10007 * bx[i - 2] + 10009 * bx[i - 1] + 87277) % w;

    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> cx[i];
    for (int i = k; i < n; i++)
        cx[i] = (10007 * cx[i - 2] + 10009 * cx[i - 1] + 87277) % h;

    cin >> k;
    for (int i = 0; i < k; i++)
        cin >> dx[i];
    for (int i = k; i < n; i++)
        dx[i] = (10007 * dx[i - 2] + 10009 * dx[i - 1] + 87277) % w;
    ///End of input
    int row[h], col[w];
    for (int i = 0; i < h; i++)
        row[i] = i;
    for (int i = 0; i < w; i++)
        col[i] = i;

    int table[h][w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            table[i][j] = i * w + j;

    for (int i = 0; i < n; i++)
        if (query[i] == 'c')
            swap(col[bx[i]], col[dx[i]]);
        else if (query[i] == 'r')
            swap(row[ax[i]], row[cx[i]]);
        else if (query[i] == 'f') {
            int r1 = row[ax[i]], c1 = col[bx[i]],
                r2 = row[cx[i]], c2 = col[dx[i]];
            swap(table[r1][c1], table[r2][c2]);
        }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            //cout << table[i][j] << " ";
        }
        //cout << endl;
    }

    int res[h][w];
    for (int i = 0; i < h; i++)
        for (int j = 0; j < w; j++)
            res[i][j] = table[row[i]][col[j]];

    ///Begin of output
    const int mod = 1e9 + 7;
    ll ans = 0;
    ll pow17 = 1;
    for (int i = 0; i < h; i++) {
        ll pow19 = 1;
        for (int j = 0; j < w; j++) {
            ans = (ans + ((pow17 * pow19) % mod * res[i][j]) % mod) % mod;
            pow19 = (19 * pow19) % mod;
        }
        pow17 = (pow17 * 17) % mod;
    }
    cout << ans;
    return 0;
}
close