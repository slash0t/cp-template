#include <bits/stdc++.h>

using namespace std;

hs mod = {1e9 + 7, 1e9 + 9};
typedef pair<int, int> hs;
hs operator+(hs const& a, hs const& b) {
	return {(a.first + b.first) % mod.first, (a.second + b.second) % mod.second};
}
hs operator-(hs const& a, hs const& b) {
	return {(a.first - b.first + mod.first) % mod.first, (a.second - b.second + mod.second) % mod.second};
}
hs operator*(hs const& a, hs const& b) {
	return {a.first * b.first % mod.first, a.second * b.second % mod.second};
}
hs operator*(hs const& a, int b) {
	return {a.first * b % mod.first, a.second * b % mod.second};
}
struct hash_ {
	int base = 0;
	vector<hs> pol;
	int n;

	hash_ (int n_) : n(n_) {
		pol = vector<hs>(n, {0, 0});
		pol[0] = {1, 1};
		mt19937 rnd(chrono::high_resolution_clock::now().time_since_epoch().count());
		base = rnd() % 1000 + 2000;
		for (int i = 1; i < n; i++) pol[i] = pol[i - 1] * base;
	}

	vector<hs> prehash(string s) {
		int nn = s.size();
		vector<hs> res(nn);
		for (int i = 0; i < nn; i++) {
			if (i) res[i] = res[i - 1];
			hs now = pol[i] * (int)(s[i] + 1);
			res[i] = res[i] + now;
		}
		return res;
	}
};
hash_ hh(1e6);