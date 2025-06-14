#include <vector>

using namespace std;

const int M = 998244353;

struct combinatorics {
	vector<int> fact, invf, two;
	int n;

	int bp(int num, int pow) {
		int res = 1;
		while (pow) {
			if (pow & 1) res = num * res % M;
			pow >>= 1;
			num = num * num % M;
		}
		return res;
	}

	combinatorics(int nn) {
		int n = nn + 10;
		fact.assign(n, 0);
		invf.assign(n, 0);
		two.assign(n, 0);

		two[0] = 1;
		for (int i = 1; i < n; i++) two[i] = two[i - 1] * 2 % M;
		fact[0] = 1;
		for (int i = 1; i < n; i++) fact[i] = fact[i - 1] * i % M;
		invf[n - 1] = inv(fact[n - 1]);
		for (int i = n - 2; i >= 0; i--) invf[i] = invf[i + 1] * (i + 1) % M;
	}

	int inv(int n) {
		return bp(n, M - 2);
	}

	int comb(int n, int k) {
		return fact[n] * invf[n - k] % M * invf[k] % M;
	}

	int cat(int n) {
		return fact[2 * n] * invf[n] % M * invf[n + 1] % M;
	}
};
combinatorics cc(1e6);