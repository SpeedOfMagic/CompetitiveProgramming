#include <bits/stdc++.h>
using namespace std;

// Complete the reverseShuffleMerge function below.
string reverseShuffleMerge(string s) {
    int letters[26];
    for (int i = 0; i < 26; i++)
        letters[i] = 0;
    
    for (char i : s)
        letters[i - 'a']++;
    
    int shuffleContains[26];
    int resultContains[26];
    for (int i = 0; i < 26; i++) {
        shuffleContains[i] = letters[i] / 2;
        resultContains[i] = letters[i] / 2;
    }
    
    int p = 0;
    for (; letters[p] == 0; p++) {}
    
    string result = "";
    for (int iter = s.length() - 1; iter >= 0; iter--) {
        char i = s[iter];
        if (i - 'a' == p) {
            resultContains[i - 'a']--;
            result += i;
            while (resultContains[p] == 0)
                p++;
        } else {
            if (shuffleContains[i - 'a'] == 0) {
                resultContains[i - 'a']--;
                result += i;
                while (resultContains[p] == 0)
                    p++;
            } else
                shuffleContains[i - 'a']--;
        }
    }
    
    return result;
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    string s;
    getline(cin, s);

    string result = reverseShuffleMerge(s);

    fout << result << "\n";

    fout.close();

    return 0;
}
