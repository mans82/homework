#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, k;
	cin >> n >> k;

	priority_queue<pair<int, int>> jq;

	for (int i = 0; i < n; i++) {
		int l, r;
		cin >> l >> r;

		jq.push({r, l});
	}

	int lastempty = jq.top().first;
	vector<int> timeline(lastempty);

	while (!jq.empty()) {
		auto curtask = jq.top();
		jq.pop();

		int r = curtask.first;
		int l = curtask.second;

		int timei = r;

		while (timei >= l && timeline[timei] >= k) timei--;

		if (timei < l) {
			cout << "NO" << endl;
			return 0;
		}

		timeline[timei]++;
	}

	cout << "YES" << endl;
}
