# ifndef PORE_H_
# define PORE_H_
# include "../include/header.h"

class Pore {

    protected:
        int id_;
        double radius_;
        std::set<int> connections_;

    private:
        std::tuple<double, double> coordinates_;
        std::vector< containers::Tuple3D<double> > pore_family_;

    public:
        Pore() = default;
        Pore(std::tuple<double, double> coordinates, int id, double radius, 
        std::set<int> connections, std::vector<containers::Tuple3D<double> > pore_family):
            id_{id},
                radius_{radius},
                    connections_{std::move(connections)},
                        coordinates_{std::move(coordinates)},
                            pore_family_{std::move(pore_family)} {};

        Pore(const Pore&) = default;
        Pore& operator=(const Pore &) = default;
        Pore(Pore &&) noexcept;
        Pore& operator=(Pore &&) noexcept;
        virtual ~Pore() = default;
        int getID() {return id_;}
        std::tuple<double, double> getCoordinates() {return coordinates_;};
        double getRadius() const {return radius_;};
        std::set<int> getConnections() {return connections_;}
        std::vector< containers::Tuple3D<double> > getPoreFamily() const {return pore_family_;};
        void setConnections(std::set<int> new_connections) {connections_ = new_connections;}
        friend std::ofstream& operator<<(std::ofstream &, const Pore &);
};

# endif