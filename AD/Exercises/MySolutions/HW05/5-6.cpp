#include <bits/stdc++.h>

using namespace std;

class DisjointSets {
private:
	int n;
	vector<int> set;
	vector<int> h;

public:
	DisjointSets(int n): n(n), set(n), h(n, 1) {
		for (int i = 0; i < n + 1; i++) set[i] = i;
	}

	int find(int x) {
		if (x != set[x]) set[x] = find(set[x]);
		return set[x];
	}

	void merge(int x, int y) {
		int set_x = find(x);
		int set_y = find(y);

		if (set_x == set_y) return;

		if (h[set_x] > h[set_y]) set[set_y] = set_x;
		else set[set_x] = set_y;
		if (h[set_x] == h[set_y]) h[set_y]++;
	}

};

int kruskal(int n, vector<vector<int>>& edge, int pre_add, int ignore_edge) {
	DisjointSets sets(n);
	int res = 0;

	if (pre_add != -1) {
		sets.merge(edge[pre_add][1], edge[pre_add][2]);
		res += edge[pre_add][0];
	}

	for (int i = 0; i < edge.size(); i++) {
		if (i == ignore_edge) continue;

		auto& cur_edge = edge[i];

		// ignore if it makes a loop
		if (sets.find(cur_edge[1]) == sets.find(cur_edge[2])) continue;

		sets.merge(cur_edge[1], cur_edge[2]);
		//cout << "merged " << cur_edge[1] << ", " << cur_edge[2] << endl;
		//for (int i = 0; i < n; i++) cout << "find(" << i << ") = " << sets.find(i) << endl;

		res += cur_edge[0];
		//mst_edges++;
	}

	for (int i = 0; i < n; i++) {
		// If so, no mst exists
		if (sets.find(i) != sets.find(0)) return INT_MAX;
	}

	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n, m;
	cin >> n >> m;

	vector<vector<int>> edge;
	edge.reserve(m);

	for (int i = 0; i < m; i++) {
		int u, v, w;
		cin >> u >> v >> w;

		edge.push_back({w, u, v, i});
	}

	sort(edge.begin(), edge.end());

	int org_res = kruskal(n, edge, -1, -1);

	vector<int> crit, ps_crit;

	for (int i = 0; i < m; i++) {
		//int ig_res = kruskal(n, edge, -1, i);
		//int pre_res = kruskal(n, edge, i, -1);
		// cout << "ignored " << edge[i][1] << ", " << edge[i][2] << ": res = " << ig_res << endl;
		// cout << "blocked " << edge[i][1] << ", " << edge[i][2] << ": res = " << pre_res << endl;
		if (kruskal(n, edge, -1, i) > org_res) {
			crit.push_back(edge[i][3]);
		} else if (kruskal(n, edge, i, -1) == org_res) {
			ps_crit.push_back(edge[i][3]);
		}
	}

	sort(crit.begin(), crit.end());
	sort(ps_crit.begin(), ps_crit.end());

	//cout << "crit: ";
	for (auto x: crit) cout << x << ' ';
	cout << endl;
	//cout << "non_crit:";
	for (auto x: ps_crit) cout << x << ' ';
	cout << endl;

	return 0;
}
