#include <vector>
#include <string>

#define int long long

using namespace std;

vector<int> zz(string s) {
	int n = s.length();
	vector<int> z(n);
	z[0] = n;
	int start = 0, end = 0;

	for (int i = 1; i < n; i++) {
		z[i] = max(0ll, min(z[i - start], end - i));

		while (i + z[i] < n && s[i + z[i]] == s[z[i]]) {
			z[i]++;
		}

		if (z[i] + i - 1 > end) {
			end = z[i] + i - 1;
			start = i;
		}
	}

	return z;
}