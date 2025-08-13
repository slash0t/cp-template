#define _CRT_SECURE_NO_WARNINGS
#define _USE_MATH_DEFINES

#include <bits/stdc++.h>

using namespace std;

#define int long long
#define ld long double
#define nl "\n"
#define pb push_back
#define xx first
#define yy second
#define cinn(a) for (int i = 0; i < (int) a.size(); i++) cin >> a[i];
#define coutt(a) for (int i = 0; i < (int) a.size(); i++) cout << a[i] << (i == a.size() - 1 ? nl : " ");
#define sortt(a) sort(a.begin(), a.end());
#define rev(a) reverse(a.begin(), a.end());
#define hi(a) (--a.end())
#define lo(a) a.begin()
#define ll(a) int a; cin >> a;
#define vi(a, n) vector<int> a(n); cinn(a);
#define forn(i, n) for (int i = 0; i < n; i++)
#define nfor(i, n) for (int i = n; i >= 0; i--)
#define foreach(i, st) for (auto & i : st)

template<class T, class G>
ostream& operator<<(ostream& os, const pair<T, G>& p) {
    os << p.first << " " << p.second << nl;
    return os;
}

template<class T, class G>
istream& operator>>(istream& is, pair<T, G>& p) {
	is >> p.first >> p.second;
	return is;
}

template<class T>
ostream& operator<<(ostream& os, const vector<T>& a) {
    for (int i = 0; i < (int) a.size(); i++) {
		os << a[i];
		if (i != a.size() - 1) os << " ";
	}
    return os;
}

template<class T>
istream& operator>>(istream& is, vector<T>& a) {
	for (int i = 0; i < (int) a.size(); i++) {
		is >> a[i];
	}
	return is;
}

const int inf = 2e18;
const int N = 2e7;
const int M = 998244353;

void solve() {
	ll(n);
	vector<pair<int, string>>a(n);
	cin >> a;
	cout << a;
}

signed main()
{
	//freopen("magic.in", "r", stdin);
	//freopen("magic.out", "w", stdout);
#ifdef SLASHOT
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	long long start = chrono::high_resolution_clock::now().time_since_epoch().count();
#endif
	ios_base::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cout << fixed;
	cout.precision(10);

	int tests = 1;
	// cin >> tests;
	while (tests--) solve();

#ifdef SLASHOT
	cout << nl << "TIME ms: ";
	cout << (chrono::high_resolution_clock::now().time_since_epoch().count() - start) / 1e6 << nl;
#endif
	return 0;
}