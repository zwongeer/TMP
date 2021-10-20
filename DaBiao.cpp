// #if __cplusplus < 201703L
// #   error "require c++ 17"
// #endif
#include <array>
#include <iostream>


template <int NUM, int i>
struct _getdigits {
    static constexpr int getV() {
        if constexpr(NUM) return _getdigits<NUM/10, i + 1>::value;
        else return i;
    }
    static constexpr int value = getV();
    // static constexpr int value = NUM == 0 ? i : _getdigits<NUM/10, i + 1>::value;
};

template <int NUM>
struct getdigits {
    static constexpr int value = NUM < 0 ? -1 : _getdigits<NUM, 0>::value;
};

template <int NUM, int i>
struct _getreversed {
    static constexpr int getV() {
        if constexpr (NUM) return _getreversed<NUM/10, i * 10 + NUM % 10>::value;
        else return i;
    }
    static constexpr int value = getV();
    // static constexpr int value = NUM == 0 ? _getreversed<NUM/10, i*10 + NUM % 10>::value : i;
};
template <int NUM>
struct getreversed {
    static constexpr int value = NUM < 0 ? -1 : _getreversed<NUM, 0>::value;
};

struct Results {
    int digits;
    int reversedNum;
};

using std::cin, std::cout, std::endl;
template <int N, int i>
struct _make {
    static constexpr void f(std::array<Results, N>& arr) {
        arr[i].digits = getdigits<i>::value;
        arr[i].reversedNum = getreversed<i>::value;
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