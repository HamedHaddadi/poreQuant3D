# pragma once

# include <iostream>
# include <math.h>
# include <string>
# include <vector>
# include <array>
# include <cstdlib>
# include <glob.h>

namespace utilities {

   /* template <typename T>
    auto Radius(T coord) -> decltype(coord) {
        T sum = 0;
        sum += ::pow(coord, 2);
        return sum;
    }

    template <typename T1, typename ... Tn>
    auto Radius(T1 coord, Tn ... coords) -> decltype(coord) {
        T1 sum = 0;
        sum += Radius(coord);
        sum += Radius(coords ...);
        return ::sqrt(sum);
    }
    */

    // non recursive version
    template <typename ... Cs>
    auto Radius(const Cs ... coords) {
        auto sum{0};
        auto coordinates = std::array{coords ...};
        for (auto && coord:coordinates) {
            sum += ::pow(coord, 2);
        }
        return ::sqrt(sum);
    }

    void makedir(std::string dirname);
    void listdir(std::vector<std::string> &, std::string);
    int minRes(int, int);
    int maxRes(int, int);
}