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


struct opdeque {
	stack<pair<int, int>> in, out;
	int init = 1ll << 60;

	opdeque() : in(), out() {}

	int size() {
		return in.size() + out.size();
	}

	int f(int a, int b) {
		return min(a, b);
	}

	int get(int p) {
		if (in.size() == 0) {
			if (out.size() == 0) return init;
			return out.top().second;
		}
		if (out.size() == 0) {
			return in.top().second;
		}
		int value = f(in.top().second, out.top().second);
		return value;
	}

	void push_back(int num) {
		int value;
		if (in.size()) {
			value = in.top().second;
		} else {
			value = init;
		}
		value = f(value, num);
		in.push({ num, value });
	}

	void push_front(int num) {
		int value;
		if (out.size()) {
			value = out.top().second;
		} else {
			value = init;
		}
		value = f(value, num);
		out.push({ num, value });
	}

	void fix() {
		bool swapped = 0;
		if (out.size() == 0) {
			swap(in, out);
			swapped = 1;
		}

		int sz1 = out.size() / 2;
		int sz2 = out.size() - sz1;

		stack<int> st;
		queue<int> q;
		for (int i = 0; i < sz1; i++) {
			st.push(out.top().first);
			out.pop();
		}
		for (int i = 0; i < sz2; i++) {
			q.push(out.top().first);
			out.pop();
		}
		while (q.size()) {
			int now = q.front(); q.pop();
			push_back(now);
		}
		while (st.size()) {
			int now = st.top(); st.pop();
			push_front(now);
		}

		if (swapped) swap(in, out);
	}

	int pop_front() {
		if (out.size() == 0) {
			fix();
		}
		int res = out.top().first;
		out.pop();
		return res;
	}

	int pop_back() {
		if (in.size() == 0) {
			fix();
		}
		int res = in.top().first;
		in.pop();
		return res;
	}
};