#include <bits/stdc++.h>

using namespace std;

int main() {

	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cout << fixed << setprecision(1);

	priority_queue<int, vector<int>, greater<int>> upper;
	priority_queue<int, vector<int>, less<int>> lower;

	int x;
	double l_med = 0;

	while (cin >> x) {
		if (x == -1) break;

		//cout << "upper size: " << upper.size() << endl;
		//cout << "lower size: " << lower.size() << endl;

		if (!upper.empty() && x > upper.top()) upper.push(x);
		else lower.push(x);

		
		 while (!upper.empty() && (signed int)upper.size() - (signed int)lower.size() > 1) {
			lower.push(upper.top());
			upper.pop();
		}

		 while (!lower.empty() && (signed int)lower.size() - (signed int)upper.size() > 1) {
			upper.push(lower.top());
			lower.pop();
		}

		//cout << "upper size: " << upper.size() << endl;
		//cout << "lower size: " << lower.size() << endl;

		if (upper.empty()) cout << (double)(l_med = lower.top()) << endl;
		else if (lower.empty()) cout << (double)(l_med = upper.top()) << endl;
		else if (upper.size() > lower.size()) {
			cout << (double)(l_med = upper.top()) << endl;
		} else if (lower.size() > upper.size()) {
			cout << (double)(l_med = lower.top()) << endl;
		} else {
			cout << (double)(l_med = (double)(lower.top() + upper.top()) / 2.0) << endl;
		}	
	}

	return 0;

}
