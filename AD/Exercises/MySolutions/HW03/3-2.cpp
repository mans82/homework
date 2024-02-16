#include <bits/stdc++.h>

using namespace std;

unordered_map<int, vector<int>> adj;

pair<int, vector<int>> solve(int node);

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n, m;
	cin >> n >> m;

	for (int i = 0; i < m; i++) {
		int u, v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	pair<int, vector<int>> ans {INT_MAX, {}};

	for (int i = 0; i < n; i++) {
		auto curans = solve(i);
		if (curans.first < ans.first) ans = curans;
	}

	cout << ans.first << endl;
	for (auto n : ans.second) cout << n << ' ';
	cout << endl;


	return 0;

}

pair<int, vector<int>> solve(int node) {

	if (adj[node].size() < 2) return {INT_MAX, {}};

	queue<int> bfsq;
	unordered_map<int, int> dep, par;
	unordered_set<int> visited;

	bfsq.push(node);
	dep[node] = 0;
	par[node] = -1; // dummy
	
	bool end = false;

	int u, v;

	while (!end) {
		auto curn = bfsq.front();
		bfsq.pop();

		for (auto neigh: adj[curn]) {
			if (neigh == par[curn]) continue;

			if (visited.find(neigh) != visited.end()) {
				u = neigh;
				v = curn;
				end = true;
				break;
			}

			visited.insert(neigh);
			dep[neigh] = dep[curn] + 1;
			par[neigh] = curn;
			bfsq.push(neigh);
		}
	}

	vector<int> res;

	for (int i = u; i != node; i = par[i]) res.push_back(i);
	res.push_back(node);

	reverse(res.begin(), res.end());

	for (int i = v; i != node; i = par[i]) res.push_back(i);
	res.push_back(node);

	return {dep[u] + dep[v] + 1, res};
}
