#include <bits/stdc++.h>

using namespace std;

int n, m;
vector<vector<int>> edge;

vector<int> bellford(int start, vector<bool>& visited) {

	vector<int> dist(n, INT_MAX);
	vector<int> par(n, -1);

	dist[start] = 0;
	
	for (int i = 0; i < n - 1; i++) {
		for (auto& e: edge) {
			int u = e[0], v = e[1], w = e[2];

			if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
				// update dist
				dist[v] = dist[u] + w;
				par[v] = u;
			}

		}
	}

	int cycle_node = -1;

	// check cycle
	for (auto& e: edge) {
		int u = e[0], v = e[1], w = e[2];

		if (dist[u] != INT_MAX && dist[v] > dist[u] + w) {
			// cycle found!
			cycle_node = u;
			break;
		}
	}

	if (cycle_node == -1) return {};

	for (int i = 0; i < n; i++) cycle_node = par[cycle_node];

	vector<int> res;
	res.push_back(cycle_node);
	
	int cur_node = par[cycle_node];

	while (cur_node != cycle_node) {
		res.push_back(cur_node);
		cur_node = par[cur_node];
	}

	res.push_back(cur_node);

	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n >> m;

	vector<bool> visited(n, false);
	edge.reserve(m);
	
	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		edge.push_back({u, v, w});
	}


	for (int i = 0; i < n; i++) {
		auto res = bellford(i, visited);

		if (!res.empty()) {
			cout << res.size() - 1 << endl;
			for (int i = res.size() - 1; i >= 0; i--) cout << res[i] << ' ';
			cout << endl;
			return 0;
		}
	}

	cout << -1 << endl;
	return 0;
}

