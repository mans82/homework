#include <bits/stdc++.h>

using namespace std;

int main() {

	string s1, s2;

	getline(cin, s1);
	getline(cin, s2);

	const int n = s1.size();

	unordered_map<char, char> charr;

	for (int i = 0; i < n; i++) {
		if (charr.find(s2[i]) == charr.end()) {
			charr[s2[i]] = s1[i];
		} else {
			if (charr[s2[i]] != s1[i]) {
				cout << "false" << endl;
				return 0;
			}
		}
	}

	charr.clear();

	for (int i = 0; i < n; i++) {
		if (charr.find(s1[i]) == charr.end()) {
			charr[s1[i]] = s2[i];
		} else {
			if (charr[s1[i]] != s2[i]) {
				cout << "false" << endl;
				return 0;
			}
		}
	}


	cout << "true" << endl;
	return 0;

}
