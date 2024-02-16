#include <bits/stdc++.h>

using namespace std;

vector<int> arr;
vector<bool> sol;
vector<bool> res;

int wholesum = 0;
int curmin = INT_MAX;

void solve(int csum, int count, int i) {
	const int n = arr.size();

	if (count > n / 2 || i >= n) return;
	if (count == n / 2) {
		if (abs(csum - (wholesum - csum)) < curmin) {
			curmin = abs(csum - (wholesum - csum));
			res = sol;
		}
	} else {
		sol[i] = 0;
		solve(csum, count, i + 1);
		sol[i] = 1;
		solve(csum + arr[i], count + 1, i + 1);
		sol[i] = 0;
	}
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	arr.resize(n);
	sol.resize(n, 0);

	for (int i = 0; i < n; i++) {
		cin >> arr[i];
		wholesum += arr[i];
	}

	solve(0, 0, 0);

	for (int i = 0; i < n; i++) {
		if (res[i]) cout << arr[i] << ' ';
	}

	cout << endl;
	return 0;

}
