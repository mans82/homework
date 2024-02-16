#include <bits/stdc++.h>

using namespace std;

unordered_map<int, int> parent;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m, d;
	cin >> n >> m >> d;

	vector<vector<int>> adj(n);

	for (int i = 0; i < m; i++) {
		int u, v, c;
		cin >> u >> v >> c;

		if (c == 1) {
			adj[u].push_back(v);
			adj[v].push_back(u);
		} else {
			int new_node = adj.size();

			adj[u].push_back(new_node);
			adj[v].push_back(new_node);
			adj.push_back({u, v});
		}
		
	}

	queue<int> bfsq;
	queue<int> dep;
	unordered_set<int> visited;
	bfsq.push(0);
	dep.push(0);

	int path_len;

	while (true) {
		auto curn = bfsq.front();
		auto curd = dep.front();
		bfsq.pop();
		dep.pop();

		if (curn == d) {
			path_len = curd;
			break;
		}

		for (auto neigh: adj[curn]) {
			if (visited.find(neigh) != visited.end()) continue;
			visited.insert(neigh);

			parent[neigh] = curn;

			bfsq.push(neigh);
			dep.push(curd + 1);
		}
	}

	cout << path_len << endl;

	vector<int> path;

	for(int i = d; i != 0; i = parent[i]) path.push_back(i);

	cout << "0 ";
	for (int i = path.size() - 1; i >= 0; i--) {
		if (path[i] < n) cout << path[i] << ' ';
	}

	cout << endl;
	return 0;
}
