#include <vector>

using namespace std;

// vector<int> lp(n + 1, 0), pr;

void getera(vector<int> & lp, vector<int> & pr) {
	int n = 99;

	for (int i = 2; i <= n; i++) {
		if (lp[i] == 0) {
			lp[i] = i;
			pr.push_back(i);
		}

		for (int p : pr) {
			if (p * i > n || p > lp[i]) break;
			lp[p * i] = p;
		}
	}
}