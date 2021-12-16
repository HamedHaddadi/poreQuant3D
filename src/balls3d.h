# ifndef BALLS3D_H_
# define BALLS3D_H_

# include "header.h"
# include "domain3d.h"
# include "balls.h"
# include "maxball3d.h"
# include "pore3d.h"

class Domain3D;

class Balls3D:public Balls {
    
    private:
        std::vector<MaxBall3D> max_balls_;
        std::vector<MaxBall3D>:: iterator balls_it_;
        std::vector<Pore3D> pores_;
        std::vector<Pore3D>::iterator pores_it_;
    
    public:
        Balls3D() = default;
        void generateBalls(Domain3D &);
        virtual void ballsToCSV();
        virtual void poresToCSV();
        virtual void generatePores();
        virtual ~Balls3D() = default;
};


# endif