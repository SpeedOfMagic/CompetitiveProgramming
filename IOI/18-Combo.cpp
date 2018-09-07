/** Solution
1. I can find first letter by simple divide & conquer approach, which demands 2 calls.
2. It's impossible to find only next character by having at most 1 call of press function.
So, instead of that, I'll try to find next two characters.
3. To find them, I can note that there are at most 3 possible different characters.
Also, I can call press function once for at most 4 prefixes; result is maximum of all of them.
4. So, I just ask one question, then suitable one after answer of that (rows 53 - 77) or not.
5. It takes 2 questions for 2 characters and 1 question for 1 character.
6. To find the last letter, I can do that by simple divide & conquer approach, which demands 2 calls.
7. Amount of made queries = 2 + (n - 2) + 2 = n + 2, which gives AC.
**/
#include "combo.h"
#include <bits/stdc++.h>
using namespace std;
#define sz(a) (int) a.size()
string guess_sequence(int N) {
	string ans = "";
	
	string l1 = "A", l2 = "B", l3 = "X";
	
	int c = press("AB");
	if (c) {
		c = press("A");
		if (c) {
			ans += "A";
			l1 = "Y";
		} else {
			ans += "B";
			l2 = "Y";
		}
	} else {
		c = press("X");
		if (c) {
			ans += "X";
			l3 = "Y";
		} else
			ans += "Y";
	}
	
	while (sz(ans) < N) {
		if (sz(ans) + 1 == N) {
			string v = ans + l1 + ans + l2;
			//cout << v << endl;
			c = press(v) - sz(ans);
			if (c) {
				v = ans + l1;
			//cout << v << endl;
				c = press(v) - sz(ans);
				if (c)
					ans += l1;
				else
					ans += l2;
			} else
				ans += l3;
		} else {
			string v = ans + l1 + l1 + ans + l1 + l2 + ans + l2 + l1;
			//cout << v << endl;
			c = press(v) - sz(ans);
			if (c == 0)
				ans += l3;
			else if (c == 1) {
				string v = ans + l2 + l2;
			//cout << v << endl;
				c = press(v) - sz(ans);
				if (c == 0)
					ans += l1 + l3;
				else if (c == 1)
					ans += l2 + l3;
				else
					ans += l2 + l2;
			} else {
				string v = ans + l1 + l1;
			//cout << v << endl;
				c = press(v) - sz(ans);
				if (c == 0)
					ans += l2 + l1;
				else if (c == 1)
					ans += l1 + l2;
				else
					ans += l1 + l1;
			}
		}
	}
	
	return ans;
}
