#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m, k;
	cin >> n >> m >> k;

	vector<vector<pair<int, int>>> ws(n+1);

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		ws[u].push_back({v, w});
	}

	priority_queue<pair<int, int>> pq;
	vector<int> dist(n + 1, INT_MAX);
	dist[0] = dist[k] = 0;

	pq.push({0, k});

	int res = 0;

	while (!pq.empty()) {
		auto top = pq.top();
		pq.pop();

		int cur_w = top.first;
		int cur_node = top.second;

		res = max(res, cur_w);

		for (auto neigh: ws[cur_node]) {
			int neigh_node = neigh.first;
			int neigh_w = neigh.second;

			if (dist[neigh_node] > dist[cur_node] + neigh_w) {
				dist[neigh_node] = dist[cur_node] + neigh_w;
				pq.push({dist[neigh_node], neigh_node});
			}
		}
	}

	//cout << visited.size() << endl;
	if (find(dist.begin(), dist.end(), INT_MAX) != dist.end()) cout << -1;
	else cout << *max_element(dist.begin(), dist.end());

	cout << endl;

	return 0;
}

