#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> inp;
	inp.reserve(m);

	for (int i = 0; i < m; i++) {
		int start, end, value;
		cin >> start >> end >> value;

		inp.push_back({end - 1, start - 1, value});
	}

	sort(inp.begin(), inp.end());

	map<int, long long> dp;
	dp[0] = 0;

	for (int i = 0; i < m; i++) {
		int cur_end = inp[i][0];
		int cur_start = inp[i][1];
		int cur_val = inp[i][2];

		auto last_job = dp.rbegin();
		auto last_doable_job = prev(dp.upper_bound(cur_start));

		long long new_res = last_doable_job->second + cur_val;

		if (new_res > last_job->second)
			dp[cur_end] = new_res;
	}

	cout << dp.rbegin()->second << endl;
	return 0;
}
