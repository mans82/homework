#include <bits/stdc++.h>

using namespace std;

double res = 0;

void solve(int node, double p, int par, int dep, vector<vector<int>>& adj) {

	if (adj[node].size() == 1 && adj[node][0] == par) {
		res += p * dep;
		return;
	}
	
	int denum = adj[node].size();
	if (par != -1) denum--;

	for (auto neigh: adj[node]) {
		if (neigh == par) continue;

		solve(neigh, p / (double)denum, node, dep + 1, adj);
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(nullptr);
	cout.tie(nullptr);

	int n;
	cin >> n;

	vector<vector<int>> adj(n + 1);

	for (int i = 0; i < n - 1; i++) {
		int u, v;
		cin >> u >> v;

		adj[u].push_back(v);
		adj[v].push_back(u);
	}

	solve(1, 1.0, -1, 0, adj);

	cout << fixed << setprecision(7) << res << endl;
	return 0;
}
