#include <bits/stdc++.h>
using namespace std;

string change(string s) {
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] >= 'A' && s[i] <= 'Z') s[i] += 32;
	}
	return s;
}

int fx(string s) {
	int len = s.size(), p = 0;
	while (s[p] == '0' && p < len) p++;
	if (p > 0 && s[p] == 'b') return 2;
	if (p > 0 && s[p] == 'x') return 16;
	if (p > 0) return 8;
	return 10;
}

bool fushu(string s) {
	int len = s.size();
	for (int i = 0; i < len; i++) {
		if (s[i] == '-') return 1;
	}
	return 0;
}

char* _pow(int n) {
	char *ans = new char[105];
	memset(ans, 0, 105);
	ans[0] = 1;
	int len = 0;
	while (n--) {
		int jw[105];
		memset(jw, 0, sizeof(jw));
		for (int i = 0; i < 100; i++) {
			ans[i] = (ans[i] - jw[i]) * 2 + jw[i];
			if (ans[i] >= 10) {
				int tmp = jw[i + 1] = ans[i] / 10;
				ans[i] %= 10;
				if (ans[i + 1] == 0) {
					bool flag = 1;
					for (int j = i + 1; j < 100; j++) {
						if (ans[j] != 0) 
							flag = 0;
					}
					ans[i + 1] += tmp;
					if (flag) {
						break;
					}
				}
				else ans[i + 1] += tmp;
			}
		}
	}
	for (int i = 100; i < 105; i++) ans[i] = 0;
	return ans;
}

bool check(string s) {
	for (int i = s.size() - 1; i >= 0; i--) 
		if (s[i] != 0) return true;
	return false;
}

struct node {
	bool data[129];
	void init() {
		memset(data, 0, 129);
	}
	void copy(node o) {
		for (int i = 0; i < 128; i++) {
			data[i] = o.data[i];
		}
		return;
	}
	void in() {
		init();
		int p = 0;
		string s;
		cin >> s;
		s = change(s);
		int res = fx(s);
		if (res == 16) {
			for (int i = s.size() - 1; i >= 2; i--) {
				int a = 0;
				if (s[i] >= '0' && s[i] <= '9') a = s[i] - '0';
				else if (s[i] >= 'a' && s[i] <= 'z') a = s[i] - 'a' + 10;
				int q = p;
				while (a != 0) {
					data[q++] = a & 1;
					a >>= 1;
				}
				p += 4;
			}
		}
		if (res == 2) {
			for (int i = s.size() - 1; i >= 0; i--) {
				data[i] = s[i] - '0';
			}
		}
		if (res == 8) {
			for (int i = s.size() - 1; i >= 0; i--) {
				int a = 0;
				if (s[i] >= '0' && s[i] <= '9') a = s[i] - '0';
				int q = p;
				while (a != 0) {
					data[q++] = a & 1;
					a >>= 1;
				}
				p += 3;
			}
		}
		if (res == 10) {
			string s1 = s;
			int p = 0;
			for (int i = 0; i < s1.size(); i++) {
				if (s[i] < '0' || s[i]>'9') s1[i] = 0;
				else s1[i] -= 48;
			}
			while (p < 128 && check(s1)) {
				data[p++] = s1[s1.size() - 1] & 1;
				for (int i = 0; i < s1.size(); i++) {
					int x = s1[i];
					if (x & 1) {
						if (i + 1 < s1.size()) {
							s1[i + 1] += 10;
						}
					}
					s1[i] = (x >> 1);
				}
			}
		}
		if (fushu(s)) buma();
		return;
	}
	void out(bool flag = 1) {
		if (flag) cout << "0x";
		if (data[127]) {
			cout << "-";
			node New;
			New.copy(*this);
			New.fbuma();
			New.out(0);
			return;
		}
		stringstream ss;
		for (int i = 0; i < 128; i += 4) {
			int x = data[i] + 2 * data[i + 1] + 4 * data[i + 2] + 8 * data[i + 3];
			if (x < 10) ss << x;
			else {
				char a = x - 10 + 'a';
				ss << a;
			}
		}
		string ans;
		ss >> ans;
		int len = ans.size() - 1;
		while (ans[len] == '0' && len > 0) len--;
		for (int i = len; i >= 0; i--) cout << ans[i];
		return;
	}
	void _10out() {
		if (data[127]) {
			cout << "-";
			node New;
			New.copy(*this);
			New.fbuma();
			New._10out();
			return;
		}
		char ans[105];
		memset(ans, 0, 105);
		for (int i = 0; i < 127; i++) {
			if (data[i]) {
				char* tmp = _pow(i);
				for (int j = 0; j < 100; j++) {
					ans[j] += tmp[j];
					if (ans[j] >= 10) {
						ans[j + 1]++;
						ans[j] -= 10;
					}
				}
			}
		}
		for (int i = 0; i < 100; i++) 
			ans[i] += 48;
		int p = 99;
		while (ans[p] == 48 && p > 0) p--;
		for (int i = p; i >= 0; i--)
			cout << ans[i];
	}
	void buma() {
		for (int i = 0; i < 128; i++) data[i] = !data[i];
		if (data[0]) {
			int p = 1;
			while (data[p] && p < 128) p++;
			for (int i = 0; i < p; i++) {
				data[i] = 0;
			}
			if (p < 128) {
				data[p] = 1;
			}
		}
		else data[0] = 1;
		return;
	}
	void fbuma() {
		int p = 0;
		while (!data[p] && p < 127) p++;
		if (p < 127) {
			for (int i = 0; i < p; i++) {
				data[i] = 1;
			}
			data[p] = 0;
		}
		for (int i = 0; i < 128; i++) {
			data[i] = !data[i];
		}
		return;
	}
	void ll() {
		node tmp2;
		tmp2.init();
		if (data[127]) tmp2.data[0] = 1;
		for (int i = 1; i < 128; i++) {
			tmp2.data[i] = data[i - 1];
		}
		for (int i = 0; i < 128; i++) {
			data[i] = tmp2.data[i];
		}
	}
	void rr() {
		node tmp2;
		tmp2.init();
		if (data[0]) tmp2.data[1] = 1;
		for (int i = 0; i < 127; i++) {
			tmp2.data[i] = data[i + 1];
		}
		for (int i = 0; i < 128; i++) {
			data[i] = tmp2.data[i];
		}
	}
	int getlen() {
		int i;
		for (i = 127; i >= 0; i--) {
			if (data[i] != 0) break;
		}
		return i + 1;
	}
	int operator[] (int i) {
		return data[i];
	}
	void swap(node* o) {
		node New;
		New.copy(*o);
		(*o).copy(*this);
		copy(New);
		return;
	}
	node operator+ (const node o) {
		node New;
		New.init();
		for (int i = 0; i < 128; i++) {
			if ((New.data[i] && (data[i] ^ o.data[i])) || (data[i] && (New.data[i] ^ o.data[i])) || (o.data[i] && (New.data[i] ^ data[i]))) {
				New.data[i] = 0;
				New.data[i + 1] = 1;
			}
			else if (New.data[i] && data[i] && o.data[i]) {
				New.data[i] = 1;
				New.data[i + 1] = 1;
			}
			else if ((New.data[i] && !(data[i] || o.data[i])) || (data[i] && !(New.data[i] || o.data[i])) || (o.data[i] && !(New.data[i] || data[i]))) {
				New.data[i] = 1;
			}
			else if (!New.data[i] && !data[i] && !o.data[i]) {
				New.data[i] = 0;
			}
		}
		return New;
	}
	node operator* (const node o) {
		node tmp, ans;
		tmp.init();
		ans.init();
		for (int i = 0; i < 128; i++) {
			if (o.data[i]) {
				tmp.init();
				for (int j = 0; j < 128; j++) tmp.data[j] = data[j];
				for (int j = 0; j < i; j++) tmp.ll();
				node ans2;
				ans2.init();
				for (int j = 0; j < 128; j++) ans2.data[j] = ans.data[j];
				ans = ans2 + tmp;
			}
		}
		return ans;
	}
	node operator- (node o) {
		node ans;
		ans.init();
		if (o.data[127]) o.fbuma();
		else o.buma();
		ans = (*this) + o;
		return ans;
	}
	node operator/ (node o) {
		node tmp, ans, one;
		tmp.copy(*this);
		ans.init();
		one.init();
		one.data[0] = 1;
		if (o == ans) return ans;
		if (o > tmp) return ans;
		if (o == tmp) return one;
		while (tmp.data[0] == 0 && o.data[0] == 0) {
			tmp = tmp >> 1;
			o = o >> 1;
		}
		while (tmp >= o) {
			//tmp._10out();
			//cout << endl;
			tmp = tmp - o;
			ans = ans + one;
		}
		return ans;
	}
	bool operator== (node o) {
		for (int i = 0; i < 128; i++) if (data[i] != o.data[i]) return 0;
		return 1;
	}
	bool operator!= (node o) {
		return !((*this) == o);
	}
	bool operator< (node o) {
		node a1, b1;
		a1.copy(*this);
		b1.copy(o);
		bool a = data[127], b = o.data[127];
		if (a == 1 && b == 0) return 1;
		if (a == 0 && b == 1) return 0;
		if (a == 1 && b == 1) {
			a1.fbuma();
			b1.fbuma();
		}
		if (a1.getlen() != b1.getlen()) return a1.getlen() < b1.getlen();
		for (int i = 126; i >= 0; i--) {
			if (a1.data[i] != b1.data[i]) return a1.data[i] < b1.data[i];
		}
		return 0;
	}
	bool operator<= (node o) {
		return ((*this) < o) || ((*this) == o);
	}
	bool operator> (node o) {
		return !((*this)<=o);
	}
	bool operator>= (node o) {
		return ((*this) > o) || ((*this) == o);
	}
	node operator<< (int x) {
		node New;
		New.copy(*this);
		for (int i = 127; i >= x; i--) {
			New.data[i] = New.data[i - x];
		}
		for (int i = x; i >= 0; i--) New.data[i] = 0;
		return New;
	}
	node operator>> (int x) {
		node New;
		New.copy(*this);
		for (int i = 0; i < 127 - x; i++) {
			New.data[i] = New.data[i + x];
		}
		for (int i = 127 - x; i < 127; i++) New.data[i] = 0;
		return New;
	}
};

int main() {
	//freopen("out", "w", stdout);
	node a, b, c;
	a.init();
	b.init();
	c.init();
	string op = "";
	a.in();
	b.in();
	cin >> op;
	if (op == "+") c = a + b;
	else if (op == "-") c = a - b;
	else if (op == "*") c = a * b;
	else if (op == "/") c = a / b;
	else if (op == "<") cout << (a < b) << endl;
	else if (op == ">") cout << (a > b) << endl;
	else if (op == "<=") cout << (a <= b) << endl;
	else if (op == ">=") cout << (a >= b) << endl;
	else if (op == "==") cout << (a == b) << endl;
	else if (op == "!=") cout << (a != b) << endl;
	/*for (int i = 127; i >= 0; i--) {
		cout << a[i];
	}
	cout << endl;
	for (int i = 127; i >= 0; i--) {
		cout << b[i];
	}
	cout << endl;
	for (int i = 127; i >= 0; i--) {
		cout << c[i];
	}
	cout << endl;*/
	c._10out();
	return 0;
}