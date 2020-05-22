#include <iostream>
#include <string>
#include <vector>

using std::string;
typedef unsigned long long ull;

struct Data {
    string pattern, text;
};

Data read_input() {
    Data data;
    std::cin >> data.pattern >> data.text;
    return data;
}

void print_occurrences(const std::vector<int>& output) {
    for (size_t i = 0; i < output.size(); ++i)
        std::cout << output[i] << " ";
    std::cout << "\n";
}

std::vector<int> get_occurrences(const Data& input) {
    const string& s = input.pattern, t = input.text;
    std::vector<int> ans;
    int n = t.size();
    int m = s.size();
    int base = 263;
    int mod = 1e9 + 7;
    long long h = 0;
    long long b = 1;
    long long h1 = 0;

    if(n < m) return ans;
    for(int i = 0; i < m; ++i){
        h = (h*base + s[i])%mod;
        h1 = (h1*base + t[i])%mod;
    }
    for(int i = 0; i < m-1; ++i){
        b = (b*base)%mod;
    }

    if(h == h1) ans.push_back(0);
    for(int i = 1; i <= n - m; ++i){
        h1 = (h1 - t[i-1]*b%mod + mod)%mod;
        h1 = (h1*base + t[i+m-1])%mod;
        if(h1 == h){
            ans.push_back(i);
        }
    }

    return ans;
}


int main() {
    std::ios_base::sync_with_stdio(false);
    print_occurrences(get_occurrences(read_input()));
    return 0;
}
