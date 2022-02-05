# ifndef PORE3D_H_
# define PORE3D_H_

# include "../include/header.h"
# include "../include/pore.h"

class Pore3D: public Pore {

    private:
        std::tuple<double, double, double> coordinates_;
        std::vector<types::Tuple4D> pore_family_;
    
    public:
        Pore3D() = default;
        Pore3D(std::tuple<double, double, double> coordinates, int id, double radius, 
            std::set<int> connections, std::vector<types::Tuple4D> pore_family) {
                      id_ = id;
                      radius_ = radius;
                      coordinates_ = std::move(coordinates);
                      connections_ = std::move(connections);
                      pore_family_ = std::move(pore_family);

        };
        virtual ~Pore3D() = default;
        std::tuple<double, double, double> getCoordinates() {return coordinates_; }
        std::vector<types::Tuple4D> getPoreFamily() const {return pore_family_;}
        friend std::ofstream& operator<<(std::ofstream & out_stream, const Pore3D & pore) {
           out_stream<<pore.id_<<","<<std::get<0>(pore.coordinates_)<<","
            <<std::get<1>(pore.coordinates_)<<","
                <<std::get<2>(pore.coordinates_)<<","
                    <<pore.radius_;
            return out_stream;
        }
};

# endif 