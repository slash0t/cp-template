#include <vector>	

using namespace std;

struct sparse_table {
	int n, r;
	vector<vector<int>> t;
	vector<int> visual_studio_enjoyer;

	sparse_table(vector<int>& a) {
		n = a.size();

		visual_studio_enjoyer.resize(n + 1);
		visual_studio_enjoyer[0] = 0;
		for (int i = 1; i <= n; i++) {
			visual_studio_enjoyer[i] = visual_studio_enjoyer[i - 1];
			if ((1ll << (visual_studio_enjoyer[i] + 1)) <= i) {
				visual_studio_enjoyer[i]++;
			}
		}

		r = visual_studio_enjoyer[n] + 1;
		t.resize(r, vector<int>(n));
		for (int i = 0; i < n; ++i) t[0][i] = a[i];
		for (int k = 1; k < r; ++k) {
			for (int i = 0; i + (1ll << k) - 1 < n; ++i) {
				t[k][i] = f(t[k - 1][i], t[k - 1][i + (1ll << (k - 1))]);
			}
		}
	}

	int get(int l, int r) {
		int k = visual_studio_enjoyer[r - l + 1];
		return f(t[k][l], t[k][r - (1ll << k) + 1]);
	}

	int f(int x, int y) {
		return min(x, y);
	}
};