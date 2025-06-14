#include <vector>	

using namespace std;

struct bit2d {
	int n, m;

	vector<vector<int>> tree;

	bit2d(int n, int m) : n(n), m(m) {
		tree = vector<vector<int>>(n, vector<int>(m));
	}

	int sum(int x, int y) {
		int res = 0;
		for (int i = x; i >= 0; i = (i & (i + 1)) - 1) {
			for (int j = y; j >= 0; j = (j & (j + 1)) - 1) {
				res += tree[i][j];
			}
		}
		return res;
	}

	int sum(int x1, int y1, int x2, int y2) {
		x1--;
		y1--;
		return sum(x2, y2) - sum(x2, y1) - sum(x1, y2) + sum(x1, y1);
	}

	void add(int x, int y, int dif = 1) {
		for (int i = x; i < n; i = i | (i + 1)) {
			for (int j = y; j < m; j = j | (j + 1)) {
				tree[i][j] += dif;
			}
		}
	}
};