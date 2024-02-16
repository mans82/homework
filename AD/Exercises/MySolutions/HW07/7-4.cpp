#include <bits/stdc++.h>

using namespace std;

vector<bool> sol;
int n;
int res = 0;

void solve(int i) {
	if (i == n) {
		res++;
		return;
	}

	for (int j = 0; j < n; j++) {
		if (!sol[j] && (((j + 1) % (i + 1) == 0) || ((i + 1) % (j + 1) == 0))) {
			sol[j] = 1;
			solve(i + 1);
			sol[j] = 0;
		}
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	cin >> n;

	sol.resize(n, 0);

	solve(0);

	cout << res << endl;

	return 0;

}
