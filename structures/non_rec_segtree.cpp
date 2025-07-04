#include <vector>	

using namespace std;

struct segtree {
	vector<int> t;
	int n;

	int ZERO = 0;

	segtree(int nn) : n(nn) {
		t.assign(2 * n, ZERO);
		build();
	}

	segtree(vector<int>& a) {
		n = a.size();
		t.assign(2 * n, ZERO);
		for (int i = 0; i < n; i++) t[i + n] = a[i];
		build();
	}

	int f(int x, int y) {
		return x + y;
	}

	void build() {
		for (int i = n - 1; i > 0; --i) t[i] = f(t[i << 1], t[i << 1 | 1]);
	}

	void upd(int p, int value) {
		for (t[p += n] = value; p > 1; p >>= 1) t[p >> 1] = f(t[p], t[p ^ 1]);
	}

	int get(int l, int r) {
		int res = ZERO;
		for (l += n, r += n; l < r; l >>= 1, r >>= 1) {
			if (l & 1) res = f(res, t[l++]);
			if (r & 1) res = f(res, t[--r]);
		}
		return res;
	}
};