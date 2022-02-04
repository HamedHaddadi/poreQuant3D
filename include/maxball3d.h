# ifndef MAXBALL3D_H_
# define MAXBALL3D_H_

# include "header.h"
# include "maxball.h"

class MaxBall3D: public MaxBall {

    private:
        std::tuple<double, double, double> coordinate_;
   
    public:
        MaxBall3D(std::tuple<double, double, double> coordinate, int id, double radius, double threshold) {
            coordinate_ = std::move(coordinate);
            id_ = id;
            radius_ = radius;
            threshold_ = threshold;
            siblings_.insert(id);
        }
        virtual ~MaxBall3D() = default;
        std::tuple<double, double, double> getCoordinates() {return coordinate_; }
        void addToParents(const MaxBall3D &);
        bool fullyIncludedIn(const MaxBall3D &) const;
        bool overlapsWith(const MaxBall3D &) const;
        friend constexpr bool operator!=(const MaxBall3D &, const MaxBall3D &);
        friend constexpr bool operator==(const MaxBall3D &, const MaxBall3D &);
        friend constexpr bool operator>=(const MaxBall3D &, const MaxBall3D &);
        friend constexpr bool operator<(const MaxBall3D &, const MaxBall3D &); 
        friend std::ofstream& operator<<(std::ofstream &, const MaxBall3D &);      
};

# endif 