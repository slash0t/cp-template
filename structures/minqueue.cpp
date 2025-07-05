#include <bits/stdc++.h>

using namespace std;

struct opqueue {
	stack<pair<int, int>> in, out;
	function<int(int, int)> f;
	int init;

	opqueue(function<int(int, int)> f_, int init_) : in(), out(), f(f_), init(init_) {}

	static opqueue minqueue() {
		return opqueue([](int a, int b) {return min(a, b); }, 1ll << 62);
	}

	static opqueue maxqueue() {
		return opqueue([](int a, int b) {return max(a, b); }, -(1ll << 62));
	}

	int size() {
		return in.size() + out.size();
	}

	int get() {
		int value = init;
		if (out.size()) {
			value = f(value, out.top().second);
		}
		if (in.size()) {
			value = f(value, in.top().second);
		}
		return value;
	}

	void push_back(int num) {
		int value = num;
		if (in.size()) {
			value = f(value, in.top().second);
		}
		in.push({ num, value });
	}

	int pop_front() {
		if (out.size() == 0) {
			while (in.size()) {
				int num = in.top().first; in.pop();
				int value = num;
				if (out.size()) value = f(num, out.top().second);
				out.push({ num, value });
			}
		}
		int res = out.top().first;
		out.pop();
		return res;
	}
};
