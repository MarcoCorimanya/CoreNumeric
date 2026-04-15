#pragma once
#include <concepts>
#include <iterator>
#include <type_traits>
#include <cmath>

namespace core_numeric {

template <typename C>
concept Iterable = requires(C c) {
    std::begin(c);
    std::end(c);
};

template <typename T>
concept Addable = requires(T a, T b) {
    { a + b } -> std::same_as<T>;
};

template <typename T>
concept Divisible = requires(T a, std::size_t n) {
    { a / n } -> std::same_as<T>;
};

template <typename T>
concept Comparable = requires(T a, T b) {
    { a > b } -> std::convertible_to<bool>;
};

template <Iterable C>
requires Addable<typename C::value_type>
auto sum(const C& container) {
    using T = typename C::value_type;
    T result{};
    for (const auto& v : container) result = result + v;
    return result;
}

template <Iterable C>
requires Addable<typename C::value_type> && Divisible<typename C::value_type>
auto mean(const C& container) {
    using T = typename C::value_type;
    auto s = sum(container);
    std::size_t count = 0;
    for (auto& _ : container) ++count;

    if constexpr (std::is_integral_v<T>)
        return static_cast<double>(s) / count;
    else
        return s / count;
}

template <Iterable C>
requires Addable<typename C::value_type>
auto variance(const C& container) {
    using T = typename C::value_type;
    auto m = mean(container);
    T acc{};
    std::size_t count = 0;

    for (const auto& v : container) {
        auto diff = v - m;
        acc = acc + diff * diff;
        ++count;
    }

    if constexpr (std::is_integral_v<T>)
        return static_cast<double>(acc) / count;
    else
        return acc / count;
}

template <Iterable C>
requires Comparable<typename C::value_type>
auto max(const C& container) {
    auto it = std::begin(container);
    auto best = *it;
    ++it;

    for (; it != std::end(container); ++it)
        if (*it > best) best = *it;

    return best;
}

template <Iterable C, typename F>
requires Addable<std::invoke_result_t<F, typename C::value_type>>
auto transform_reduce(const C& container, F func) {
    using T = std::invoke_result_t<F, typename C::value_type>;
    T result{};
    for (const auto& v : container) result = result + func(v);
    return result;
}

template <Addable T, typename... Ts>
auto sum_variadic(T first, Ts... args) {
    return (first + ... + args);
}

template <typename... Ts>
requires Addable<std::common_type_t<Ts...>>
auto mean_variadic(Ts... args) {
    auto s = (args + ...);
    constexpr std::size_t n = sizeof...(args);

    if constexpr (std::is_integral_v<decltype(s)>)
        return static_cast<double>(s) / n;
    else
        return s / n;
}

template <typename... Ts>
requires Addable<std::common_type_t<Ts...>>
auto variance_variadic(Ts... args) {
    auto m = mean_variadic(args...);
    auto acc = (((args - m) * (args - m)) + ...);
    constexpr std::size_t n = sizeof...(args);
    return acc / n;
}

template <Comparable T, typename... Ts>
auto max_variadic(T first, Ts... args) {
    T result = first;
    ((result = args > result ? args : result), ...);
    return result;
}

}