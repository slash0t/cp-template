#include <bits/stdc++.h>

using namespace std;

struct opqueue {
	stack<pair<int, int>> in, out;
	function<int(int, int)> f;
	int init;

	opqueue(function<int(int, int)> f_, int init_): in(), out(), f(f_), init(init_) {}

	int get() {
		int minn = init;
		if (out.size()) {
			minn = f(minn, out.top().second);
		}
		if (in.size()) {
			minn = f(minn, in.top().second);
		}
	}

	void push_back(int num) {
		int minn = num;
		if (in.size()) {
			minn = f(minn, in.top().second);
		}
		in.emplace(num, minn);
	}

	int pop_front() {
		if (out.size()) {
			while (in.size()) {
				int num = in.top().first; in.pop();
				int minn = num;
				if (out.size()) minn = f(num, out.top().second);
				out.push({num, minn});
			}
		}
		int res = out.top().first;
		out.pop();
		return res;
	}
};
#define minqueue(name) opqueue name([](int a, int b) {return min(a, b);}, 1e18);
#define maxqueue(name) opqueue name([](int a, int b) {return max(a, b);}, -1e18);