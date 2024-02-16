#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> w;

vector<vector<int>> floyd(int n) {
	vector<vector<int>> dist(n, vector<int>(n, INT_MAX));

	for (int i = 0; i < n; i++) dist[i][i] = 0;

	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			dist[i][j] = w[i][j];
			//cout << "w[" << i << "][" << j << "] = " << w[i][j] << endl;
		}
	}

	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] == INT_MAX || dist[k][j] == INT_MAX) continue;
				dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
			}
		}
	}

	return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, t;
	cin >> n >> m >> t;

	w.resize(n, vector<int>(m, INT_MAX));

	for (int i = 0; i < n; i++) w[i][i] = 0;

	for (int i = 0; i < m; i++) {
		int s, d, wi;
		cin >> s >> d >> wi;

		s--;
		d--;

		w[s][d] = w[d][s] = wi;
	}

	for (int i = 0; i < t; i++) {
		int k;
		cin >> k;

		auto dist = floyd(k);

		//cout << "for floyd(" << k << "):" << endl;
		//for (auto& row: dist) {
		//	for (auto e: row) cout << e << ' ';
		//	cout << endl;
		//}

		//cout << endl;

		int ws = INT_MAX;

		int s;
		int cur_s = 0;

		for (auto& row: dist) {
			bool flag = true;
			int sum = 0;
			for (auto elem: row) {
				if (elem == INT_MAX) {
					flag = false;
					break;
				} else {
					sum += elem;
				}
			}

			if (flag) {
				if (sum < ws) {
					ws = sum;
					s = cur_s;
				}
			}

			cur_s++;
		}

		if (ws != INT_MAX) cout << s + 1 << ' ' << ws;
		else cout << 0;

		cout << endl;
	}



	return 0;
}

