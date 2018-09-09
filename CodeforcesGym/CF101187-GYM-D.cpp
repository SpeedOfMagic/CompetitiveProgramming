#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int) a.size()
#define pb push_back
typedef vector<int> vint;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(0); cout.tie(0);
    int n, m;
    cin >> n >> m;
    string mp[n];
    for (int i =0 ; i < n ; i++)
        cin >> mp[i];

    vint rfRow[n][26], rfCol[m][26];
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            rfRow[i][mp[i][j] - 'a'].pb(j);

    for (int j = 0; j < m; j++)
        for (int i = 0; i < n; i++)
            rfCol[j][mp[i][j] - 'a'].pb(i);

    int q;
    cin >> q;
    const int inf = 1e9;
    pair<int, int> minRow[26], minCol[26];
    for (; q; q--) {
        int r, c;
        cin >> r >> c;
        r--; c--;

        for (int i = 0; i < 26; i++) {
            int right = upper_bound(rfRow[r][i].begin(), rfRow[r][i].end(), c) - rfRow[r][i].begin();
            int left = right - 1;
            if (left != -1 && rfRow[r][i][left] == c)
                left--;
            minRow[i] = {inf, i};
            if (left != -1)
                minRow[i].first = rfRow[r][i][left];
            if (right != sz(rfRow[r][i]) && (minRow[i].first == inf || c - minRow[i].first > rfRow[r][i][right] - c))
                minRow[i].first = rfRow[r][i][right];

            int down = upper_bound(rfCol[c][i].begin(), rfCol[c][i].end(), r) - rfCol[c][i].begin();
            int up = down - 1;
            if (up != -1 && rfCol[c][i][up] == r)
                up--;
            minCol[i] = {inf, i};
            if (up != -1)
                minCol[i].first = rfCol[c][i][up];
            if (down != sz(rfCol[c][i]) && (minCol[i].first == inf || rfCol[c][i][down] - r < r - minCol[i].first))
                minCol[i].first = rfCol[c][i][down];
        }
        sort(minRow, minRow + 26, [&c](pair<int, int> a, pair<int, int> b) {return abs(a.first - c) < abs(b.first - c);});
        sort(minCol, minCol + 26, [&r](pair<int, int> a, pair<int, int> b) {return abs(a.first - r) < abs(b.first - r);});
        //cout << r << " " << minRow[0].first << " " << minRow[0].second << " " << minRow[1].first << " " << minRow[1].second << endl;
        //cout << c << " " << minCol[0].first << " " << minCol[0].second << " " << minCol[1].first << " " << minCol[1].second << endl;
/* 1 2 2 1
3 2
ab
cd
ef
1
1 1
*//* 2 1 1 2
3 3
cac
ccc
bcc
1
2 2
*/
        int dist = inf;
        int ansC = -1, ansR = -1;
        for (int i = 0; i < 26; i++) {
            if (minRow[i].first == inf)
                break;
            for (int j = 0; j < 26; j++) //max. 2 elements
                if (minCol[j].first == inf)
                    break;
                else if (minRow[i].second == minCol[j].second)
                    continue;
                else {
                    int pc = minRow[i].first;
                    int pr = minCol[j].first;
                    int pos = abs(pc - c) + abs(pr - r);
                    if (pos < dist) {
                        dist = pos;
                        ansC = pc;
                        ansR = pr;
                    }
                }
        }

        if (ansC == -1)
            cout << -1 << endl;
        else
            cout << r + 1 << " " << ansC + 1 << " " << ansR + 1 << " " << c + 1 << endl;
    }

    return 0;
}
