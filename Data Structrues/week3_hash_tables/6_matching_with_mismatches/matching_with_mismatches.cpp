#include <iostream>
#include <vector>

using namespace std;

vector<int> solve(int k, const string &text, const string &pattern) {
	vector<int> pos;
	int m = text.size();
	int n = pattern.size();
	long long base = 263;
	long long mod = 1e9 + 7;
	vector<long long> ht(m+1,0);
	vector<long long> hp(n+1,0);
	vector<long long> bx(m+1,1);

	if(text.size() == 0 || text.size() == 0 || m < n){
		return pos;
	}
	for(int i = 1; i <= m; ++i){
		bx[i] = (bx[i-1]*base)%mod;
	}
	for(int i = 1; i <= m; ++i){
		ht[i] = (ht[i-1]*base + text[i-1])%mod;
	}
	for(int i = 1;i <= n; ++i){
		hp[i] = (hp[i-1]*base + pattern[i-1])%mod;
	}

	auto hashPattern = [&](int x,int y){
		int l = y - x + 1;
		long long curr = (hp[y+1] - hp[x]*bx[l]%mod + mod)%mod;
		return curr;
	};
	auto hashText = [&](int x,int y){
		int l = y - x + 1;
		long long curr = (ht[y+1] - ht[x]*bx[l]%mod + mod)%mod;
		return curr;
	};

	for(int i = 0; i <= m-n; ++i){
		int start = 0;
		int end = n-1;
		//cout<<"start from "<<i<<endl;
		for(int j = 0; j < k; ++j){
			if(start > end) break;
			int l = start;
			int r = end;
			int last = r + 1;
			while(l <= r){
				int mid = (l + r)>>1;
				if(hashText(i+start,i+mid) != hashPattern(start,mid)){
					last = mid;
					r = mid - 1;
				}else{
					l = mid + 1;
				}
			}
			start = last + 1;
		}
		//cout<<start<<":"<<end<<endl;
		if(start > end || hashText(start+i,end+i) == hashPattern(start,end)){
			pos.push_back(i);
		}
	}

	return pos;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	int k;
	string t, p;
	while (cin >> k >> t >> p) {
		auto a = solve(k, t, p);
		cout << a.size();
		for (int x : a)
			cout << " " << x;
		cout << "\n";
	}
}
