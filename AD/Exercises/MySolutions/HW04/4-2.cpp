#include <bits/stdc++.h>

using namespace std;

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);

	unordered_map<int, int> cntmapa, cntmapb;

	int n;
	cin >> n;

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		cntmapa[x]++;
	}

	for (int i = 0; i < n; i++) {
		int x;
		cin >> x;

		cntmapb[x]++;
	}

	vector<int> cnta;
	priority_queue<int> cntb;

	for (auto elem: cntmapa) cnta.push_back(elem.second);
	//for (auto elem: cntmapb) cntb.push_back(elem.second);
	for (auto elem: cntmapb) cntb.push(elem.second);

	//sort(cnta.begin(), cnta.end());
	//sort(cntb.begin(), cntb.end(), greater<int>());
	//reverse(cntb.begin(), cntb.end());
	//reverse(cnta.begin(), cnta.end());

	//swap(cnta, cntb);

	int res = 0;
	int startb = 0;

	for (int i = 0; i < cnta.size(); i++) {
		int cura = cnta[i];

		vector<int> tempb;

		for (int j = 0; !cntb.empty() && j < cura; j++) {
			int curb = cntb.top();
			cntb.pop();

			if (curb == 0) continue;

			tempb.push_back(curb - 1);
			res++;
		}

		for (auto v : tempb) cntb.push(v);

		//sort(cntb.begin(), cntb.end(), greater<int>());
	}

	cout << res << endl;
	return 0;
}
