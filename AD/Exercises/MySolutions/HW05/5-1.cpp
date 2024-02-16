#include <bits/stdc++.h>

using namespace std;

int delta[6][3] = {
	{1, 0, -1},
	{1, -1, 0},
	{0, -1, 1},
	{-1, 0, 1},
	{-1, 1, 0},
	{0, 1, -1}
};

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		string line;
		cin >> line;

		int curpos[3] = {0, 0, 0};

		for (auto c: line) {
			int ind = c - 'A';
			for (int j = 0; j < 3; j++) curpos[j] += delta[ind][j];
		}

		int res = 0;
		for (int j = 0; j < 3; j++) res += abs(curpos[j]);

		cout << res / 2 << endl;
	}

	return 0;
}
