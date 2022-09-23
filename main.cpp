#include <iostream>
#include <vector>
#include <unordered_map>
#include <optional>
#include <cassert>

std::pair<int, int> twoSum(const std::vector<int>& input, const int target) {
    std::unordered_map<int, int> m;
    // create hash table from the vector
    // {number, index} pairs
    // in case we have duplicate number, check if number*2 == target
    // and if yes, mark it and exit early.

    // special case - since we are using transform, we cannot cut it short.
    // might worth to make it a simple loop in this case.

    // For very long input, it might worth to also check in general if we already have it and cut the loop early.
    std::optional<std::pair<int, int>> found_pair;
    std::ignore = std::transform(input.cbegin(), input.cend(),
                                 std::inserter(m, m.end()),
                                 [i = 0, &m, target, &found_pair](const auto item) mutable -> std::pair<int, int>
                                 {
                                     if (const auto found = m.find(item); found != m.cend()) {
                                        if (item * 2  == target) {
                                            found_pair = {i, found->second};
                                        }
                                     }
                                    return {item, i++};
                                 });
    if (found_pair.has_value()){
        return found_pair.value();
    }
    for (const auto [item, idx]: m) {
        const auto to_find = target - item;
        if (const auto found = m.find(to_find); found != m.cend()) {
            const auto [f,i] = *found;
            return {idx, i};
        }
    }
    // should not happen
    return {0, 0};
}

int main() {
    {
        std::vector input{2, 7, 11, 15};
        constexpr auto target = 9;
        const auto [x, y] = twoSum(input, target);
        std::cout << x << ',' << y << '\n';
        assert(x == 1 && y == 0);
    }
    {
        std::vector input{3, 2, 4};
        constexpr auto target = 6;
        const auto [x, y] = twoSum(input, target);
        std::cout << x << ',' << y << '\n';
        assert(x == 2 && y == 1);
    }
    {
        std::vector input{3, 3};
        constexpr auto target = 6;
        const auto [x, y] = twoSum(input, target);
        std::cout << x << ',' << y << '\n';
        assert(x == 1 && y == 0);
    }
    return 0;
}
