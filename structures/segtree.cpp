#include <vector>

using namespace std;

const int inf = 1e9;

struct segtree {
	struct gett {
		int max;
	};
	struct node {
		int modify;
		gett get;
	};

	vector<node> t;
	int size;

	int NO_OPERATION = -inf;
	gett ZERO = { 0 };
	gett INITIAL = ZERO;

	segtree(int n) {
		size = 1;
		while (size < n) size *= 2;

		t.assign(size * 2 - 1, { NO_OPERATION, INITIAL });
		build(0, 0, size);
	}

	segtree(vector<int>& a) {
		int n = a.size();
		size = 1;
		while (size < n) size *= 2;

		t.assign(size * 2 - 1, { NO_OPERATION, INITIAL });
		build(a, 0, 0, size);
	}

	int modify(int a, int b, int len) {
		if (b == NO_OPERATION) return a;
		if (a == NO_OPERATION) return b;
		return a + b;
	}

	gett modify(gett a, int b, int len) {
		if (b == NO_OPERATION) return a;
		return { a.max + b };
	}

	gett unite(gett a, gett b, int len) {
		return { max(a.max, b.max) };
	}

	void build(vector<int>& a, int x, int lx, int rx) {
		if (rx - lx == 1) {
			t[x] = { NO_OPERATION, INITIAL };
			if (lx < a.size()) t[x] = { NO_OPERATION, {a[lx]} };
			return;
		}
		int m = (lx + rx) / 2;
		build(a, x * 2 + 1, lx, m);
		build(a, x * 2 + 2, m, rx);
		t[x].modify = NO_OPERATION;
		t[x].get = unite(t[x * 2 + 1].get, t[x * 2 + 2].get, rx - lx);
	}

	void build(int x, int lx, int rx) {
		if (rx - lx == 1) {
			t[x] = { NO_OPERATION, INITIAL };
			return;
		}
		int m = (lx + rx) / 2;
		build(x * 2 + 1, lx, m);
		build(x * 2 + 2, m, rx);
		t[x].modify = NO_OPERATION;
		t[x].get = unite(t[x * 2 + 1].get, t[x * 2 + 2].get, rx - lx);
	}

	void propagate(int x, int lx, int rx) {
		if (rx - lx == 1 || t[x].modify == NO_OPERATION) return;
		int m = (lx + rx) / 2;
		t[x * 2 + 1].modify = modify(t[x * 2 + 1].modify, t[x].modify, 1);
		t[x * 2 + 1].get = modify(t[x * 2 + 1].get, t[x].modify, m - lx);
		t[x * 2 + 2].modify = modify(t[x * 2 + 2].modify, t[x].modify, 1);
		t[x * 2 + 2].get = modify(t[x * 2 + 2].get, t[x].modify, rx - m);
		t[x].modify = NO_OPERATION;
	}

	void upd(int v, int l, int r, int x, int lx, int rx) {
		propagate(x, lx, rx);
		if (lx >= r || rx <= l) return;
		if (lx >= l && rx <= r) {
			t[x].modify = modify(t[x].modify, v, 1);
			t[x].get = modify(t[x].get, v, rx - lx);
			return;
		}
		int m = (lx + rx) / 2;
		upd(v, l, r, x * 2 + 1, lx, m);
		upd(v, l, r, x * 2 + 2, m, rx);
		t[x].get = unite(t[x * 2 + 1].get, t[x * 2 + 2].get, min(rx, r) - max(lx, l));
	}

	void upd(int v, int l, int r) {
		return upd(v, l, r, 0, 0, size);
	}

	gett get(int l, int r, int x, int lx, int rx) {
		propagate(x, lx, rx);
		if (lx >= r || rx <= l) return ZERO;
		if (lx >= l && rx <= r) {
			return t[x].get;
		}
		int m = (lx + rx) / 2;
		gett a = get(l, r, x * 2 + 1, lx, m);
		gett b = get(l, r, x * 2 + 2, m, rx);
		return unite(a, b, min(rx, r) - max(lx, l));
	}

	gett get(int l, int r) {
		return get(l, r, 0, 0, size);
	}
};