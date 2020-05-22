#include <iostream>
#include <vector>

using namespace std;
using namespace std;

class Solver {
	string s;
	int base;
	int mod;
	vector<long long> hx;
	vector<long long> bx;
public:	
	Solver(string s) : s(s) {	
		// initialization, precalculation
		int n = s.size();
		this->base = 263;
		this->mod = 1e9 + 7;
		this->hx = vector<long long>(n+1,0);
		this->bx = vector<long long>(n+1,1);
		for(int i = 1; i <= n; ++i){
			hx[i] = (hx[i-1]*base + s[i-1])%mod;
			bx[i] = (bx[i-1]*base)%mod;
		}
	}
	bool ask(int a, int b, int l) {
		long long h1 = (hx[a+l] - hx[a]*bx[l]%mod + mod)%mod;
		long long h2 = (hx[b+l] - hx[b]*bx[l]%mod + mod)%mod;
		if(h1 == h2) return true;
		return false;
	}
};

int main() {
	ios_base::sync_with_stdio(0), cin.tie(0);

	string s;
	int q;
	cin >> s >> q;
	Solver solver(s);
	for (int i = 0; i < q; i++) {
		int a, b, l;
		cin >> a >> b >> l;
		cout << (solver.ask(a, b, l) ? "Yes\n" : "No\n");
	}
}
