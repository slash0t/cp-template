#define _USE_MATH_DEFINES

#include <complex>
#include <vector>

using namespace std;

#define comp complex<double>
void fft(vector<comp>& a, bool inv) {
	int n = a.size();
	if (n == 1) {
		return;
	}

	vector<comp> a0(n / 2), a1(n / 2);
	for (int i = 0; i < n / 2; i++) {
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	fft(a0, 0);
	fft(a1, 0);

	double angle = 2 * M_PI / n;
	comp w(1), wn(cos(angle), sin(angle));

	for (int i = 0; i < n / 2; i++) {
		a[i] = a0[i] + w * a1[i];
		a[i + n / 2] = a0[i] - w * a1[i];
		w *= wn;
	}

	if (inv) {
		for (int i = 0; i < n; i++) a[i] /= n;
		reverse(++a.begin(), a.end());
	}
}

const int M = 998244353;

int bitPow(int num, int pow) {
	if (pow == 0) return 1;
	if (pow % 2 == 0) {
		int temp = bitPow(num, pow / 2);
		return temp * temp % M;
	}
	return bitPow(num, pow - 1) * num % M;
}

void ntt(vector<int>& a, bool inv) {
	int n = a.size();
	if (n == 1) {
		return;
	}

	vector<int> a0(n / 2), a1(n / 2);
	for (int i = 0; i < n / 2; i++) {
		a0[i] = a[2 * i];
		a1[i] = a[2 * i + 1];
	}
	ntt(a0, 0);
	ntt(a1, 0);

	int w = 1, wn = bitPow(3, (M - 1) / n);

	for (int i = 0; i < n / 2; i++) {
		a[i] = (a0[i] + w * a1[i] % M) % M;
		a[i + n / 2] = (a0[i] - w * a1[i] % M + M) % M;
		w = wn * w % M;
	}

	int nn = bitPow(n, M - 2);
	if (inv) {
		for (int i = 0; i < n; i++) a[i] = a[i] * nn % M;
		reverse(++a.begin(), a.end());
	}
}