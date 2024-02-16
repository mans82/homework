#include <bits/stdc++.h>

using namespace std;

char input[200][200];
char answer[200][200];

int n, m;

void solve(int i, int j) {
	if (i < 0 || i >= n || j < 0 || j >= m || answer[i][j] == '1' || input[i][j] == 'R') return;

	answer[i][j] = '1';

	solve(i - 1, j);
	solve(i + 1, j);
	solve(i, j - 1);
	solve(i, j + 1);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	cin >> n >> m;

	for (int i = 0; i < n; i++) {
		string line;
		cin >> line;

		for (int j = 0; j < m; j++) {
			input[i][j] = line[j];
			answer[i][j] = '0';
		}
	}

	for (int i = 0; i < n; i++) {
		solve(i, 0);
		solve(i, m - 1);
	}

	for (int j = 0; j < m; j++) {
		solve(0, j);
		solve(n - 1, j);
	}

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) cout << answer[i][j];
		cout << endl;
	}

	return 0;

}
