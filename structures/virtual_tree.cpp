#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

#define xx first
#define yy second
#define pb push_back

struct tree {
	vector<vector<int>> jump;
	vector<vector<pair<int, int>>> g;
	vector<int> depth, in, out;
	vector<bool> flag;
	int root, n, logn = 21;
	int time = 0, szflag = 0;


	tree(int nn, int r = 0) : root(r), n(nn) {
		g.assign(n, vector<pair<int, int>>());
		flag.assign(n, 0);
	}

	void add_edge(int a, int b, int w = 1) {
		g[a].pb({ b, w });
		g[b].pb({ a, w });
	}

	void count_euler(int now = -1, int prev = -1) {
		if (now == -1) {
			now = root;
			time = 0;
			in.assign(n, 0);
			out.assign(n, 0);
		}

		in[now] = time++;
		for (auto& to : g[now]) {
			if (to.xx == prev) continue;
			count_euler(to.xx, now);
		}
		out[now] = time++;
	}

	void count_depth(int now = -1, int prev = -1, int d = 0) {
		if (now == -1) {
			now = root;
			depth.assign(n, 0);
		}

		depth[now] = d;
		for (auto& to : g[now]) {
			if (to.xx == prev) continue;
			count_depth(to.xx, now, d + 1);
		}
	}

	void count_parents(int now = -1, int prev = -1) {
		if (now == -1) {
			now = root;
			jump[now][0] = root;
		}
		else {
			jump[now][0] = prev;
		}

		for (auto& to : g[now]) {
			if (to.xx == prev) continue;
			count_parents(to.xx, now);
		}
	}

	void count_lca() {
		jump.assign(n, vector<int>(logn));
		count_parents();
		count_depth();

		for (int i = 1; i < logn; i++) {
			for (int j = 0; j < n; j++) {
				jump[j][i] = jump[jump[j][i - 1]][i - 1];
			}
		}
	}

	int lca(int a, int b) {
		if (depth[a] < depth[b]) swap(a, b);

		for (int i = logn - 1; i >= 0; i--) {
			if (depth[jump[a][i]] < depth[b]) continue;
			a = jump[a][i];
		}

		if (a == b) return a;

		for (int i = logn - 1; i >= 0; i--) {
			if (jump[a][i] == jump[b][i]) continue;
			a = jump[a][i];
			b = jump[b][i];
		}

		return jump[a][0];
	}

	tree get_aux(vector<int>& s) {
		if (jump.empty()) count_lca();
		if (in.empty()) count_euler();

		vector<pair<int, int>> a;
		for (int i : s) a.pb({ in[i], i });
		sort(a.begin(), a.end());
		for (int i = 1; i < s.size(); i++) {
			int lcaa = lca(a[i].yy, a[i - 1].yy);
			a.pb({ in[lcaa], lcaa });
		}
		sort(a.begin(), a.end());
		a.erase(unique(a.begin(), a.end()), a.end());

		tree res(a.size());
		stack<int> st;
		st.push(0);
		for (int i = 1; i < a.size(); i++) {
			int curr = a[i].yy;
			int top = a[st.top()].yy;
			while (in[top] > in[curr] || out[top] < in[curr]) {
				st.pop();
				top = a[st.top()].yy;
			}
			res.add_edge(i, st.top(), depth[curr] - depth[top]);
			st.push(i);
		}
		vector<pair<int, int>> b;
		for (int i = 0; i < a.size(); i++) b.pb({ a[i].yy, i });
		sort(b.begin(), b.end());
		sort(s.begin(), s.end());
		int i = 0, j = 0;
		while (i < s.size() && j < a.size()) {
			if (s[i] == b[j].xx) {
				res.flag[b[j].yy] = 1;
				i++, j++;
			}
			else if (s[i] < b[j].xx) i++;
			else j++;
		}
		res.szflag = s.size();
		return res;
	}

	int count_marked(int& answer, int now = -1, int prev = -1) {
		if (now == -1) {
			now = root;
		}
		int res = flag[now];

		for (auto& to : g[now]) {
			if (to.xx == prev) continue;
			int temp = count_marked(answer, to.xx, now);
			res += temp;

			answer += temp * (szflag - temp) * to.yy;
		}

		return res;
	}
};