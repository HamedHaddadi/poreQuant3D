# ifndef DOMAIN3D_H_
# define DOMAIN3D_H_

# include "./header.h"
# include "./balls3d.h"

class Domain3D {

    private:
        static const int ix_[];
        static const int iy_[];
        static const int iz_[];
        static int counter_;
        int res_x_, res_y_, res_z_;
        int num_solid_{0};
        double domain_x_, domain_y_, domain_z_;
        double dx_, dy_, dz_;
        std::string output_dir_;
        std::vector< std::vector< std::vector<int> > > grid_;
        std::vector< std::vector< std::vector<int> > >::iterator row_;
        std::vector< std::vector<int> >::iterator col_;
        std::vector<int>::iterator dep_;       
    
    public:
        Domain3D(std::string filename, std::string outputdir);
        bool inDomain(int x, int y, int z);
        int nodeType(int x, int y, int z);
        std::tuple<int, int, int> getRes() {return std::make_tuple(res_x_, res_y_, res_z_); }
        void gridToCSV(std::string flag);

    friend class Balls3D;
};

# endif



