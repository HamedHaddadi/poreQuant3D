/* Domain2D class for pixel operations */
# ifndef Domain2D_H_
# define Domain2D_H_
# include "./header.h"
# include "./balls.h"


class Domain2D {
    
    private:
        static const int ix_[];
        static const int iy_[];
        static int counter_;
        int res_x_, res_y_;
        int num_solid_{0};
        double domain_x_, domain_y_;
        double dx_, dy_;
        std::string output_dir_;
        std::vector< std::vector<int> > grid_;
        std::vector< std::vector<int> >::iterator row_;
        std::vector<int>::iterator col_;
    
    public:
        Domain2D(std::string filename, std::string outputdir);
        bool inDomain(int x, int y);
        std::tuple<int, int> getRes() {return std::make_tuple(res_x_, res_y_); }
        int nodeType(int x, int y);
        void gridToCSV(std::string flag);
    
    friend class Balls;
};

# endif
