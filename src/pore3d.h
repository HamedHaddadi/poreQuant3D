# ifndef PORE3D_H_
# define PORE3D_H_

# include "header.h"
# include "pore.h"

class Pore3D: public Pore {

    private:
        std::tuple<double, double, double> coordinates_;
        std::vector< std::tuple<double, double, double, double> > pore_family_;
    
    public:
        Pore3D() = default;
        Pore3D(std::tuple<double, double, double> coordinates, int id, double radius, 
            std::set<int> connections, std::vector<std::tuple<double, double, double, double> > pore_family) {
                      id_ = id;
                      radius_ = radius;
                      coordinates_ = std::move(coordinates);
                      connections_ = std::move(connections);
                      pore_family_ = std::move(pore_family);

        };
        virtual ~Pore3D() = default;
        std::tuple<double, double, double> getCoordinates() {return coordinates_; }
        std::vector<std::tuple<double, double, double, double> > getPoreFamily() const {return pore_family_;}
};

# endif 