#include <bits/stdc++.h>

using namespace std;

int dp[1000001];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	string a, b;
	cin >> a >> b;

	dp[0] = 0;
	dp[1] = a[0] != b[0];
	int lastdiff = a[0] == b[0] ? -1 : 1;

	for (int i = 2; i <= n; i++) {

		if (a[i - 1] == b[i - 1]) dp[i] = dp[i - 1];
		else {
			if (lastdiff == -1) {
				dp[i] = dp[i - 1] + 1;
				lastdiff = i;
			} else {
				if (a[i - 1] == a[lastdiff - 1]) dp[i] = 1 + (i - lastdiff) + dp[lastdiff - 1];
				else dp[i] = (i - lastdiff) + dp[lastdiff - 1];

				dp[i] = min(dp[i], 1 + dp[i - 1]);
				lastdiff = i;
			}
		}

		//cout << "dp[" << i << "] = " << dp[i] << endl;
		//cout << "lastdiff = " << lastdiff << endl << endl;
	}

	cout << dp[n] << endl;
	return 0;
}
