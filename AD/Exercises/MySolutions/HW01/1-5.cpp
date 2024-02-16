#include <bits/stdc++.h>

using namespace std;

unordered_map<int, vector<int>> adj;
int gmax = 1;

int solve(int root, int parent, int nmin, int nmax) {

	int ldep = 0;
	int rdep = 0;

	for (auto ch: adj[root]) {
		if (ch == parent) continue;
		if (ch < root) {
			if (ch < nmin || ch > root - 1) {
				solve(ch, root, 1, INT_MAX);
			} else ldep = max(ldep, solve(ch, root, nmin, root - 1));
		} else if (ch > root) {
			if (ch < root + 1 || ch > nmax) {
				solve(ch, root, 1, INT_MAX);
			}
			else rdep = max(rdep, solve(ch, root, root + 1, nmax));
		}
	}

	int res = 1 + min(ldep, rdep);
	gmax = max(gmax, res);
	return res;
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int n, root;
	cin >> n >> root;

	for (int i = 0; i < n - 1; i++) {
		int x, y;
		cin >> x >> y;

		adj[x].push_back(y);
		adj[y].push_back(x);
	}
	
	solve(root, -1, 1, n);
	cout << (1ull << gmax) - 1ull << endl;
	return 0;
}
