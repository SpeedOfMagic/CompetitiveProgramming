#include <bits/stdc++.h>

using namespace std;

int main()
{
    int x1, x2, x3;
    cin >> x1 >> x2 >> x3;
    int kol1 =x2, kol2 = x3;
    if(x1 + x2 == x3 || x1 + x3 == x2 || x2 + x3 == x1){
        cout << 0;
        return 0;
    }
    for(int c=0; c<=x1; c++){
        kol1 = x2+c;
        kol2 = x3+(x1-c);
        if(kol1 == kol2){
            cout << 1 << endl;
            cout << c << " " << x1-c;
            return 0;
        }
    }
    for(int c=0; c<=x2; c++){
        kol1 = x1+c;
        kol2 = x3+(x2-c);
        if(kol1 == kol2){
            cout << 2 << endl;
            cout << c << " " << x2-c;
            return 0;
        }
    }
    for(int c=0; c<=x3; c++){
        kol1 = x2+c;
        kol2 = x1+(x3-c);
        if(kol1 == kol2){
            cout << 3 << endl;
            cout << c << " " << x3-c;
            return 0;
        }
    }
    cout << -1;
    return 0;
}