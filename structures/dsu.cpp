#include <vector>

using namespace std;

struct dsu {
	int n, unions;
	vector<int> t, count;

	dsu(int nn) {
		n = nn;
		unions = n;

		t.assign(n, 0);
		for (int i = 0; i < n; i++) t[i] = i;
		count.assign(n, 1);
	}

	int find(int i) {
		if (i == t[i]) return i;
		return t[i] = find(t[i]);
	}

	bool unite(int a, int b) {
		a = find(a);
		b = find(b);

		if (a == b) return 0;
		unions--;

		if (count[a] > count[b]) swap(a, b);

		t[a] = b;
		count[b] += count[a];
		return 1;
	}
};