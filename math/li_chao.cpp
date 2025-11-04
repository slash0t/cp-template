#include <algorithm>

using namespace std;

const int inf = 1e9;

struct line {
	int k = inf, m = inf;
	line() {}
	line(int k, int m) : k(k), m(m) {}
	int get(int x) {
		return k * x + m;
	}
};

struct li_chao_tree {
	struct node
	{
		line lin;
		node* l = nullptr;
		node* r = nullptr;
	};

	int n;
	node* root = nullptr;

	li_chao_tree(int _n) : n(_n) {
		root = new node();
	}

	node* upd(node* n, int tl, int tr, line L) {
		if (!n) {
			n = new node();
		}
		if (tl > tr) {
			return n;
		}
		int tm = (tl + tr) / 2;
		bool l = L.get(tl) < n->lin.get(tl);
		bool mid = L.get(tm) < n->lin.get(tm);
		bool r = L.get(tr) < n->lin.get(tr);
		if (!mid && !l && !r) {
			return n;
		}
		if (mid) {
			swap(L, n->lin);
			l = L.get(tl) < n->lin.get(tl);
			r = L.get(tr) < n->lin.get(tr);
		}
		if (l) {
			n->l = upd(n->l, tl, tm - 1, L);
		}
		else {
			n->r = upd(n->r, tm + 1, tr, L);
		}
		return n;
	}

	node* upd(line l) {
		return upd(root, 0, n - 1, l);
	}

	int get(node* n, int tl, int tr, int x) {
		if (!n || tl > tr) {
			return inf * inf;
		}
		int tm = (tl + tr) / 2;
		if (x == tm) {
			return n->lin.get(x);
		}
		if (x < tm) {
			return min(n->lin.get(x), get(n->l, tl, tm - 1, x));
		}
		else {
			return min(n->lin.get(x), get(n->r, tm + 1, tr, x));
		}
	}

	int get(int x) {
		return get(root, 0, n - 1, x);
	}
};