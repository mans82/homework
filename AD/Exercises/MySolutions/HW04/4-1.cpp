#include <bits/stdc++.h>

using namespace std;

long long input[2000][2000];
long long dp[2000][2000];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int m, n;
	cin >> m >> n;

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> input[i][j];
		}
	}

	dp[0][0] = input[0][0];

	for (int i = 1; i < m; i++) dp[i][0] = dp[i - 1][0] + input[i][0];
	for (int j = 1; j < n; j++) dp[0][j] = dp[0][j - 1] + input[0][j];

	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + input[i][j];
		}
	}

	cout << dp[m-1][n-1] << endl;
	return 0;
}
