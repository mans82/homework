#include <bits/stdc++.h>

using namespace std;

int main() {

	ios::sync_with_stdio(false);

	int n, q;
	cin >> n >> q;

	vector<int> pos(n, 0);

	vector<unsigned long long> prefix;
	
	for (int i = 0; i < q; i++) {
		int cmd;
		cin >> cmd;

		if (cmd == 1) {
			unsigned long long x;
			cin >> x;
			if (prefix.empty()) prefix.push_back(x);
			else prefix.push_back(prefix.back() + x);
		} else {
			int qn, cnt;
			cin >> qn >> cnt;

			unsigned long long sum;
			if (pos[qn - 1] == 0) {
				if (cnt == 0) sum = 0;
				else sum = prefix[cnt - 1];
			} else sum = prefix[pos[qn - 1] + cnt - 1] - prefix[pos[qn - 1] - 1];

			// if (pos[qn - 1] == 0 && cnt == 0) sum = 0;
			//else sum = prefix[pos[qn - 1] + cnt - 1];

			pos[qn - 1] += cnt;
			cout << sum << endl;
		}
	}

}
