#include <vector>

using namespace std;

struct bit {
	int n, MPOW;

	vector<int> tree;

	bit(int n) : n(n) {
		MPOW = 1;
		while ((1ll << (MPOW + 1)) <= n) MPOW++;
		tree = vector<int>(n);
	}

	bit(vector<int>& a) {
		n = a.size();
		MPOW = 1;
		while ((1ll << (MPOW + 1)) <= n) MPOW++;
		tree = vector<int>(n);
		for (int i = 0; i < n; i++) {
			tree[i] += a[i];
			if ((i | (i + 1)) < n) tree[i | (i + 1)] += tree[i];
		}
	}

	int sum(int i) {
		int res = 0;
		for (int ii = i; ii >= 0; ii = (ii & (ii + 1)) - 1) {
			res += tree[ii];
		}
		return res;
	}

	int sum(int l, int r) {
		return sum(r) - sum(l - 1);
	}

	void add(int i, int dif = 1) {
		for (int ii = i; ii < n; ii = ii | (ii + 1)) {
			tree[ii] += dif;
		}
	}

	int contains(int i) {
		return sum(i, i);
	}

	// how many before
	int order_by_key(int i) {
		return sum(0, i - 1);
	}

	// 1 based order
	int element_by_order(int ord) {
		int sum = 0;
		int ret = 0;
		for (int i = 1ll << MPOW; i; i >>= 1) {
			if (ret + (i - 1) >= n) continue;
			if (sum + tree[ret + (i - 1)] >= ord) continue;
			sum += tree[ret + (i - 1)];
			ret += i;
		}
		return ret;
	}

	int first_zero() {
		int ret = 0;
		for (int i = 1ll << MPOW; i; i >>= 1) {
			if (ret + (i - 1) >= n) continue;
			if (tree[ret + (i - 1)] < i) continue;
			ret += i;
		}
		return ret;
	}
};