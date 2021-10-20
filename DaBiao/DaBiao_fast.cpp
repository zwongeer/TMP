// #if __cplusplus < 201703L
// #   error "require c++ 17"
// #endif
// g++ -ftemplate-depth=100009 -O2 -std=c++20 $FILENAME
#include <array>
#include <iostream>

constexpr int getDigits(int num) {
    if (num < 0) return -1;
    int i = 0;
    while (num) {
        ++i;
        num /= 10;
    }
    return i;
}
constexpr int getResversedNum(int num) {
    if (num < 0) return -1;
    int i = 0;
    while (num) {
        i *= 10;
        i += num % 10;
        num /= 10;
    }
    return i;
}

struct Results {
    int digits;
    int reversedNum;
};

using std::cin, std::cout, std::endl;
template <int N, int i>
struct _make {
    static constexpr void f(std::array<Results, N>& arr) {
        arr[i].digits = getDigits(i);
        arr[i].reversedNum = getResversedNum(i);
        if constexpr (i - 1)
            _make<N, i - 1>::f(arr);
    }
};

template<int N>
constexpr std::array<Results, N + 1> make() {
    std::array<Results, N + 1> arr;
    _make<N + 1, N>::f(arr);
    return arr;
}

int main( ) {
    auto arr = make<99999>();
    int i;
    cin >> i;
    cout << "是" << arr[i].digits << "位数" << endl;
    cout << "倒过来是:" << arr[i].reversedNum << endl;
    return 0;
}
