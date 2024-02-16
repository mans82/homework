#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;
	
	int s;
	cin >> s;

	vector<int> inp(n);
	int sum = 0;

	for (int i = 0; i < n; i++) {
		cin >> inp[i];
		sum += inp[i];
	}
	
	const int halfsum = 3 * s;

	vector<vector<bool>> dp(n, vector<bool>(halfsum));
	vector<vector<bool>> trace(n, vector<bool>(halfsum, false));

	for (int i = 0; i < halfsum; i++) dp[0][i] = false;
	for (int i = 0; i < n; i++) dp[i][0] = true;

	for (int i = 1; i < n; i++) {
		for (int j = 1; j < halfsum; j++) {
			if (inp[i] <= j) {
				dp[i][j] = dp[i-1][j] || dp[i-1][j-inp[i]];
				if (dp[i-1][j-inp[i]]) trace[i][j] = true;
			} else dp[i][j] = dp[i-1][j];
		}
	}

	int j;

	for (j = s - inp[0] + 1; j < halfsum; j++) {
		if (dp[n-1][j]) break;
	}

	vector<int> res;

	for (int i = n - 1; i > 0 && j > 0; i--) {
		if (trace[i][j]) {
			res.push_back(i);
			j -= inp[i];
		}
	}

	cout << "0 ";
	for (int i = res.size() - 1; i >= 0; i--) cout << res[i] << ' ';
	cout << endl;

	return 0;


}
