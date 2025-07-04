#include <vector>	

using namespace std;

struct sqrtdec {
	int n, sq;
	vector<int> val, dval, dadd;
	sqrtdec(int nn) {
		n = nn;
		sq = 1;
		while (sq * sq < n) sq++;
		n = sq * sq;
		val = vector<int>(n);
		dval = vector<int>(sq);
		dadd = vector<int>(sq);
	}

	sqrtdec(vector<int>& a) {
		n = a.size();
		sq = 1;
		while (sq * sq < n) sq++;
		n = sq * sq;
		val = a;
		dval = vector<int>(sq);
		for (int i = 0; i < n; i++) dval[i / sq] += a[i];
		dadd = vector<int>(sq);
	}

	void push(int pos) {
		for (int i = sq * pos; i < sq * (pos + 1); i++) val[i] += dadd[pos];
		dval[pos] += sq * dadd[pos];
		dadd[pos] = 0;
	}

	int get(int l, int r) {
		int sum = 0;
		int sql = l / sq + 1;
		int sqr = r / sq - 1;
		for (int i = sql; i <= sqr; i++) {
			sum += dadd[i] * sq;
			sum += dval[i];
		}

		push(sql - 1);
		for (int i = l; i < min(r + 1, sq * sql); i++) sum += val[i];

		if (sql - 2 != sqr) {
			push(sqr + 1);
			for (int i = sq * (sqr + 1); i <= r; i++) sum += val[i];
		}
		return sum;
	}

	void upd(int l, int r, int v) {
		int sql = l / sq + 1;
		int sqr = r / sq - 1;
		for (int i = sql; i <= sqr; i++) dadd[i] += v;

		push(sql - 1);
		for (int i = l; i < min(r + 1, sq * sql); i++) {
			dval[i / sq] += v;
			val[i] += v;
		}

		if (sql - 2 != sqr) {
			push(sqr + 1);
			for (int i = sq * (sqr + 1); i <= r; i++) {
				dval[i / sq] += v;
				val[i] += v;
			}
		}
	}
};