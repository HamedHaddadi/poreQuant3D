# pragma once

# include <iostream>
# include <math.h>
# include <string>
# include <vector>
# include <cstdlib>
# include <glob.h>

namespace utilities {

    template <typename T>
    T Radius (T x, T y) {
        return ::sqrt(::pow(x, 2) + ::pow(y, 2));
    }

    template <typename T>
    T Radius3D(T x, T y, T z) {
        return ::sqrt(::pow(x, 2) + ::pow(y, 2) + ::pow(z , 2));
    }

    void makedir(std::string dirname);
    void listdir(std::vector<std::string> &, std::string);
    int minRes(int, int);
    int maxRes(int, int);
}