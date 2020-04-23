#include <iostream>
#include <vector>
using std::vector;

int fibonacci_sum_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum = 1;
    long long period = 60;
    long long cycle = 1;
    
    for(long long i = 0; i < period-1; ++i){
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
        cycle = (cycle + current)%10;
    }
    cycle = ((n/period)*cycle)%10;

    long long mod = n%period;
    if(mod == 0) return cycle;
    if(mod == 1) return cycle + 1;

    previous = 0;
    current = 1;
    sum = 1;
    for (long long i = 0; i < mod-1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
        sum = (sum + current)%10;
    }

    return (sum + cycle)%10;
}

long long get_fibonacci_partial_sum_naive(long long from, long long to) {
    long long sum = 0;
    if(from == 0) return (fibonacci_sum_naive(to) + 10)%10;
    return (fibonacci_sum_naive(to) - fibonacci_sum_naive(from-1) + 10)%10;
}

int main() {
    long long from, to;
    std::cin >> from >> to;
    std::cout << get_fibonacci_partial_sum_naive(from, to) << '\n';
}
