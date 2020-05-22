#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

using namespace std;

struct Answer {
	size_t i, j, len;
};



/*
"ababcabcdabcdef", "abcdefabcdeabcdabcab")
(5, 11, 7)
"abfoocd", "fghfooi")
(2, 3, 3)
"cool", "toolbox")
"aaa", "bb")
"aabaa", "babbaab")
(2, 3, 3)
>>> find_longest_common_substring("aaaa", "aaaa")
(0, 0, 4)
>>> find_longest_common_substring("aaaaaa", "aaaa")
(0, 0, 4)
>>> find_longest_common_substring("aaaa", "aaaaaa")
(0, 0, 4)
>>> find_longest_common_substring("aabaaa", "aaab")
(3, 0, 3)
>>> find_longest_common_substring("aaaaab", "baaaaa")
(0, 1, 5)
>>> find_longest_common_substring("baaaab", "aaaaaa")
(1, 0, 4)
>>> find_longest_common_substring("bbbbba", "aaaaab")
(5, 0, 1)
>>> find_longest_common_substring("abcabcd", "abcdabc")
(3, 0, 4)
*/
Answer solve(const string &s, const string &t) {
	Answer ans = {0, 0, 0};
	int m = s.size();
	int n = t.size();
	long long base1 = 263;
	long long mod1 = 1e9 + 7;
	long long mod2 = 100001611;
	
	vector<long long> hs1(m+1,0);
	vector<long long> ht1(n+1,0);
	vector<long long> bx1(max(m,n)+1,1);

	if(s.size() == 0 || t.size() == 0){
		return ans;
	}
	for(int i = 1; i <= max(m,n); ++i){
		bx1[i] = (bx1[i-1]*base1)%mod1;
	}
	for(int i = 1; i <= m; ++i){
		hs1[i] = (hs1[i-1]*base1 + s[i-1])%mod1;
	}
	for(int i = 1;i <= n; ++i){
		ht1[i] = (ht1[i-1]*base1 + t[i-1])%mod1;
	}

	auto check = [&](int len,long long mod,Answer & res){
		unordered_map<long long,int> cnt;

		/*calc string s*/
		for(int i = 0; i <= m-len; ++i){
			long long h = (hs1[i+len] - hs1[i]*bx1[len]%mod + mod)%mod;
			cnt[h] = i;
		}
		/*calc string t*/
		for(int i = 0; i <= n-len; ++i){
			long long h = (ht1[i+len] - ht1[i]*bx1[len]%mod + mod)%mod;
			if(cnt.count(h)){
				res.i = cnt[h];
				res.j = i;
				res.len = len;
				return true;
			}
		}

		return false;
	};

	int l = 0;
	int r = min(m,n);
	while(l <= r){
		int mid = (l+r)>>1;
		Answer curr;
		if(check(mid,mod1,curr)){
			ans = curr;
			l = mid + 1;
		}else{
			r = mid - 1;
		}
	}

	return ans;
}

int main() {
	ios_base::sync_with_stdio(false), cin.tie(0);
	string s, t;
	while (cin >> s >> t) {
		auto ans = solve(s, t);
		cout << ans.i << " " << ans.j << " " << ans.len << "\n";
	}
}
