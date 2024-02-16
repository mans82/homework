#include <bits/stdc++.h>

using namespace std;

vector<vector<pair<int, int>>> adj;

vector<long long> dijkstra(int n, int start) {

	vector<long long> dist(n, LLONG_MAX);
	dist[start] = 0;

	priority_queue<pair<long long, int>> pq;
	pq.push({0, start});

	while (!pq.empty()) {
		auto cur_v = pq.top();
		pq.pop();

		int cur_node = cur_v.second;

		for (auto neigh: adj[cur_node]) {
			int neigh_node = neigh.first;
			int neigh_w = neigh.second;

			if (dist[neigh_node] > dist[cur_node] + neigh_w) {
				dist[neigh_node] = dist[cur_node] + neigh_w;
				pq.push({dist[neigh_node], neigh_node});
			}
		}

	}
	
	return dist;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int t;
	cin >> t;

	for (int i = 0; i < t; i++) {
		int n, m, p;
		cin >> n >> m >> p;

		int s, g, h;
		cin >> s >> g >> h;

		long long gh_w = -1;

		s--;
		g--;
		h--;

		if (g > h) swap(g, h);

		adj.clear();
		adj.resize(n);

		for (int j = 0; j < m; j++) {
			int u, v, w;
			cin >> u >> v >> w;

			u--;
			v--;

			if ((u == g && v == h) || (u == h && v == g)) gh_w = w;

			adj[u].push_back({v, w});
			adj[v].push_back({u, w});
		}

		if (gh_w == -1) {
			cout << "LOL" << endl;
			return 0;
		}

		vector<int> res;
		res.reserve(n);

		auto dist = dijkstra(n, s);
		auto dist_h = dijkstra(n, h);
		auto dist_g = dijkstra(n, g);

		for (int j = 0; j < p; j++) {
			int pi;
			cin >> pi;
			pi--;

			if (dist[g] == LLONG_MAX || dist_h[pi] == LLONG_MAX) continue;
			if (dist[g] + gh_w + dist_h[pi] == dist[pi] || dist[h] + gh_w + dist_g[pi] == dist[pi]) res.push_back(pi);

		}

		sort(res.begin(), res.end());

		for (auto p: res) {
			cout << p + 1 << ' ';
		}

		cout << endl;

	}

	return 0;
}

