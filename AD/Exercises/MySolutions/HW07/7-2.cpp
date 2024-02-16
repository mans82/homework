#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	int n;
	cin >> n;

	vector<pair<long long, long long>> inp(n);

	for (int i = 0; i < n; i++) {
		cin >> inp[i].first >> inp[i].second;
	}

	long long mindist = LLONG_MAX;
	pair<long long, long long> a;
	pair<long long, long long> b;

	for (int i = 0; i < n; i++) {
		for (int j = i + 1; j < n; j++) {
			auto a_x = inp[i].first;
			auto a_y = inp[i].second;
			auto b_x = inp[j].first;
			auto b_y = inp[j].second;

			long long dist = (a_x - b_x) * (a_x - b_x) + (a_y - b_y) * (a_y - b_y);

			if (dist < mindist) {
				mindist = dist;
				a = {a_x, a_y};
				b = {b_x, b_y};
			}
		}
	}

	cout << a.first << ' ' << a.second << endl;
	cout << b.first << ' ' << b.second << endl;
	
	return 0;

}
