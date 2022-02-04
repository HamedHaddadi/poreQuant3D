# pragma once
# include <iostream>
# include <fstream>
# include <tuple>
# include <utility>
# include <algorithm>

namespace types {

    // 3d tuple of ints with << overloaded
    struct Tuple3D {
        std::tuple<double, double, double> data_;
        Tuple3D(std::tuple<double, double, double> data):data_{std::move(data)}{}
        Tuple3D& operator=(const Tuple3D&) = default;
        Tuple3D(const Tuple3D&) = default;
        Tuple3D& operator=(Tuple3D && other) noexcept {
            std::swap(data_, other.data_);
            return *this;
        }
        Tuple3D(Tuple3D && other) noexcept {
            std::swap(data_, other.data_);
        }
        ~Tuple3D() = default;
        friend std::ofstream& operator<<(std::ofstream& out_stream, const Tuple3D & tup) {
            out_stream<<std::get<0>(tup.data_)<<","
                <<std::get<1>(tup.data_)<<","
                    <<std::get<2>(tup.data_);
            return out_stream;
        }
    };

    // 4d tuple of double with << overloaded
    // useful for pore_family
    struct Tuple4D {
        std::tuple<double, double, double, double> data_;
        Tuple4D(std::tuple<double, double, double, double> data):data_{std::move(data)}{}
        Tuple4D& operator=(const Tuple4D &) = default;
        Tuple4D(const Tuple4D &) = default;
        Tuple4D& operator=(Tuple4D && other) noexcept {
            std::swap(data_, other.data_);
            return *this;
        } 
        Tuple4D(Tuple4D && other) noexcept {
            std::swap(data_, other.data_);
        }
        ~Tuple4D() = default;

        friend std::ofstream& operator<<(std::ofstream& out_stream, const Tuple4D & tup) {
            out_stream <<std::get<0>(tup.data_)<<","
                <<std::get<1>(tup.data_)<<","
                    <<std::get<2>(tup.data_)<<","
                        <<std::get<3>(tup.data_);
            return out_stream;
        }
    };
    
}