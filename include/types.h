# pragma once
# include <iostream>
# include <fstream>
# include <tuple>
# include <map>
# include <set>
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

    // adjacency list 
    struct AdjList {
        std::map<int, std::set<int> > adjacency_;
        AdjList() = default;
        AdjList(int node, int connection) {
            std::set<int> temp;
            temp.insert(connection);
            adjacency_.insert(std::make_pair(node, temp));
        }
        AdjList(int node, std::set<int> connections) {
            adjacency_[node].insert(connections.begin(), connections.end());
        }
        void insertNode(int key, const std::set<int> & connections) {
            adjacency_[key].insert(connections.begin(), connections.end());
        }

        void insertNode(int key, int connection) {
            adjacency_[key].insert(connection);
        }

        void insertNode(int && key, std::set<int> && connections) {
            adjacency_[key].insert(connections.begin(), connections.end());
        }

        friend std::ofstream& operator<<(std::ofstream& out_stream, const AdjList & adj) {
            std::map<int, std::set<int> >::const_iterator adj_iter = adj.adjacency_.cbegin();
            std::set<int>::const_iterator set_iter;            
            for (; adj_iter != adj.adjacency_.cend(); ++adj_iter) {
                out_stream<<adj_iter -> first<<":";
                set_iter = adj_iter -> second.cbegin();
                for (; set_iter != adj_iter -> second.cend(); ++set_iter) {
                    out_stream<<*set_iter<<" ";
                    if (set_iter == std::prev(adj_iter -> second.end()))
                        out_stream<<std::endl;
                }
            }
            return out_stream;
        }
    };


}