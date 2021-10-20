// http://www.purecpp.org/detail?id=2068
// https://github.com/hogliux/semimap
#include <iostream>
#include <functional>
#include <type_traits>
#include <utility>

template <auto...> struct dummy_t{};
constexpr std::size_t constexpr_strlen(const char* str) { return str[0] == 0 ? 0 : constexpr_strlen(str + 1) + 1; }

template <typename Identifier, std::size_t... I>
constexpr auto array2type(Identifier id, std::index_sequence<I...>) {
    return dummy_t<id()[I]...>{};
}
template <typename Lambda>
constexpr auto key2type(Lambda lambda) {
    return array2type(lambda, std::make_index_sequence<strlen(lambda())>{});
}

template <typename Key, typename Value>
class static_map {
public:
    template <typename Lambda>
    static Value& get(Lambda lambda) {
        static_assert(std::is_convertible_v<decltype(lambda()), Key>);
        return get_internal<decltype(key2type(lambda))>();
    }
private:
    template <typename>
    static Value& get_internal() {
        static Value value;
        return value;
    }
};

#define GETID(v) []()constexpr{return v;}
using std::cin, std::cout, std::endl;

int main(int argc, char const *argv[])
{
    using map = static_map<std::string, std::function<void()>>;
    map::get(GETID("1")) = []{cout << "call 1" << endl;};
    map::get(GETID("2")) = []{cout << "call 2" << endl;};

    map::get(GETID("1"))();
    map::get(GETID("2"))();
    return 0;
}
