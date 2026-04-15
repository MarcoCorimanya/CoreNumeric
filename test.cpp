#include <iostream>
#include <vector>
#include <string>
#include "core_numeric.hpp"

int main() {

    std::vector<double> data{1.0, 2.0, 3.0};

    auto s = core_numeric::sum(data);
    auto m = core_numeric::mean(data);
    auto v = core_numeric::variance(data);
    auto mx = core_numeric::max(data);

    std::cout << s << std::endl;
    std::cout << m << std::endl;
    std::cout << v << std::endl;
    std::cout << mx << std::endl;

    auto tr = core_numeric::transform_reduce(data, [](double x){
        return x * x;
    });

    std::cout << tr << std::endl;

    auto s1 = core_numeric::sum_variadic(1,2,3,4);
    auto s2 = core_numeric::mean_variadic(1.0,2.0,3.0,4.0);
    auto s3 = core_numeric::variance_variadic(1.0,2.0,3.0,4.0);
    auto s4 = core_numeric::max_variadic(1.0,2.7,3.0,4.0);

    std::cout << s1 << std::endl;
    std::cout << s2 << std::endl;
    std::cout << s3 << std::endl;
    std::cout << s4 << std::endl;

}