#include <iostream>
#include <cassert>

using namespace std;

int fibonacci_sum_squares_fast(long long n) {
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
        cycle = (cycle + current*current)%10;
    }
    cycle = ((n/period)*cycle)%10;

    long long mod = n%period;
    if(mod == 0) return cycle;
    if(mod == 1) return (cycle + 1)%10;

    previous = 0;
    current = 1;
    sum = 1;
    for (long long i = 0; i < mod-1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = (tmp_previous + current)%10;
        sum = (sum + current*current)%10;
    }

    return (sum + cycle)%10;
}

int fibonacci_sum_squares_naive(long long n) {
    if (n <= 1)
        return n;

    long long previous = 0;
    long long current  = 1;
    long long sum      = 1;

    for (long long i = 0; i < n - 1; ++i) {
        long long tmp_previous = previous;
        previous = current;
        current = tmp_previous + current;
        sum += current * current;
    }

    return sum % 10;
}

void test_solution() {
    for (int n = 1; n < 1000; ++n)
    {
        cout<<n<<endl;
        assert(fibonacci_sum_squares_naive(n) == fibonacci_sum_squares_fast(n));
    }
        
}


int main() {
    long long n = 0;
    std::cin >> n;
    //std::cout << fibonacci_sum_squares_naive(n);
    //test_solution();
    std::cout << fibonacci_sum_squares_fast(n);
}
