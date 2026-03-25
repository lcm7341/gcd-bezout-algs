#include <cstdio>
#include <utility>
#include <vector>
#include <algorithm>

struct Eq {
    int remainder;
    int quotient;
    int multiplied_by;
    int result;
    int remainder_mult;
};

int euclid_gcd(int a, int b) {
    int high = std::max(a, b);
    int low = std::min(a, b);

    if (high % low == 0) return low;
    return euclid_gcd(low, high % low);
}

std::pair<int, int> bezout(int a, int b) {
    int goal = euclid_gcd(a,b);
    std::vector<Eq> equations;

    int high = std::max(a, b);
    int low = std::min(a, b);

    int m, n;

    while (high % low != 0) {
        Eq equation = {
            high % low,
            low,
            high / low,
            high,
            1
        };
        equations.push_back(equation);

        int temp = high;
        high = low;
        low = temp % low;
    }


    std::vector<Eq> backwards_equations;
    std::vector<Eq> backwards_equations_copy;

    for (auto eq : equations) {
        Eq backwards = {
            eq.result,
            eq.quotient,
            -eq.multiplied_by,
            eq.remainder,
            1
        };
        backwards_equations.push_back(backwards);
        backwards_equations_copy.push_back(backwards);
    }

    for (int i = 1; i < backwards_equations.size(); i++) {
        auto& eq = backwards_equations[i];
        auto& last_eq = backwards_equations[i-1];
        eq.quotient = last_eq.quotient;
        eq.remainder_mult = last_eq.remainder_mult;
        eq.remainder_mult *= eq.multiplied_by;
        eq.multiplied_by *= last_eq.multiplied_by;
        eq.remainder = last_eq.remainder;

        if (i >= 2) {
            auto& last_last_eq = backwards_equations[i-2];
            eq.multiplied_by += last_last_eq.multiplied_by;
            eq.remainder_mult += last_last_eq.remainder_mult;
        } else {
            eq.multiplied_by += 1;
        }
    }

    n = backwards_equations[backwards_equations.size() - 1].multiplied_by;
    m = backwards_equations[backwards_equations.size() - 1].remainder_mult;

    return std::make_pair(m, n);
}

int main() {
    int a, b;
    printf("Enter two integers separated by a space: ");
    scanf("%i %i", &a, &b);
    int gcd = euclid_gcd(a,b);
    printf("gcd(%i,%i) = %i\n", a, b, gcd);

    std::pair<int, int> bezout_pair = bezout(a, b);
    int m = bezout_pair.first;
    int n = bezout_pair.second;

    int high = std::max(a, b);
    int low = std::min(a, b);

    printf("bezout identity: %i = %i(%i) + %i(%i)", gcd, high, m, low, n);
}
