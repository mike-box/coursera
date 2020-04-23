#include <iostream>

long long get_pisano_period(long long m){
    if(m <= 1) return 0;

    long long previous = 0;
    long long current  = 1;
    
    for (long long i = 0; i < (m*m); ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
        if(previous == 0 && current == 1){
            return i+1;
        }
    }

    return 0;
}

long long get_fibonacci_huge_naive(long long n, long long m) {
    if (n <= 1)
        return n;

    
    long long previous = 0;
    long long current  = 1;
    long long sum = 1;
    long long period = get_pisano_period(m);
    
    long long mod = n%period;
    if(mod == 0) return 0;
    if(mod == 1) return 1;
    for (long long i = 0; i < mod-1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%m;
    }

    return current;
}

int main() {
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonacci_huge_naive(n, m) << '\n';
}
