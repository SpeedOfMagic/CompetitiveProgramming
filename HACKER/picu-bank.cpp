//1 2 03 04 05 06 07 08 09 10 11
//2 7 12 17 20 25 31 36 41 46 51
#include <iostream>

using namespace std;

int main() {
    int t;
    cin >> t;
    while (t --> 0) {
        long long d, a, m, b, x;
        cin >> d >> a >> m >> b >> x;
        long long ans = 0;
        long long amount = a * m + b;
        long long need = x - d;
        long long p = need / amount;
        need -= p * amount;
        ans += p * (m + 1);
        p = need / a + !!(need % a);
        ans += p;
        cout << ans << endl;
    }
}