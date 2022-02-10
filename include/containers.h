# pragma once 
# include <iostream>
# include <map>
# include <tuple>
# include <set>
# include <utility>
# include <algorithm>

namespace containers {

template <typename T> class Tuple3D;
template <typename T>
std::ofstream& operator<<(std::ofstream &, const Tuple3D<T> &);

template <typename T> class Tuple4D;
template <typename T>
std::ofstream& operator<<(std::ofstream &, const Tuple4D<T> &);

template <typename T>
class Tuple3D {
    private:
        std::tuple<T, T, T> data_;
    public:
        Tuple3D(std::tuple<T, T, T> data):data_{std::move(data)}{}
        Tuple3D<T>& operator=(const Tuple3D<T>&) = default;
        Tuple3D(const Tuple3D<T> &) = default;
        Tuple3D<T>& operator=(Tuple3D<T> && other) noexcept {
            std::swap(data_, other.data_);
            return *this;
        }
        Tuple3D(Tuple3D<T> && other) noexcept {
            std::swap(data_, other.data_);
        }
        ~Tuple3D() = default;
        friend std::ofstream& operator<< <T>(std::ofstream &, const Tuple3D<T> &);
};

template <typename T>
std::ofstream& operator<<(std::ofstream & out_stream, const Tuple3D<T> & tup3D) {
    out_stream<<std::get<0>(tup3D.data_)<<","
        <<std::get<1>(tup3D.data_)<<","
            <<std::get<2>(tup3D.data_);
    return out_stream;
}

template <typename T>
class Tuple4D {
    private:
        std::tuple<T, T, T, T> data_;
    public:
        Tuple4D(std::tuple<T, T, T, T> data):data_{std::move(data)}{}
        Tuple4D<T> & operator=(const Tuple4D<T> &) = default;
        Tuple4D(const Tuple4D<T> &) = default;
        Tuple4D<T>& operator=(Tuple4D<T> && other) noexcept {
            std::swap(data_, other.data_);
            return *this;
        }
        Tuple4D(Tuple4D<T> && other) noexcept {
            std::swap(data_, other.data_);
        }
        ~Tuple4D() = default;
        friend std::ofstream& operator<< <T> (std::ofstream &, const Tuple4D<T> &);
};

template <typename T>
std::ofstream& operator<<(std::ofstream & out_stream, const Tuple4D<T> & tup4D) {
    out_stream<<std::get<0>(tup4D.data_)<<","
        <<std::get<1>(tup4D.data_)<<","
            <<std::get<2>(tup4D.data_)<<","
                <<std::get<3>(tup4D.data_);
    return out_stream;
}

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