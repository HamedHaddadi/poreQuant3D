
# include "../include/domain3d.h"

// using a Q19 lattice type
const int Domain3D::ix_[] = {1,-1,0,0,0,0,1,-1,1,-1,0,0,1,-1,1,-1,0,0};
const int Domain3D::iy_[] = {0,0,1,-1,0,0,1,-1,0,0,1,-1,-1,1,0,0,1,-1};
const int Domain3D::iz_[] = {0,0,0,0,1,-1,0,0,1,-1,1,-1,0,0,-1,1,-1,1};
int Domain3D::counter_{0};

Domain3D::Domain3D(std::string filename, std::string output_dir) {

    std::string line;
    std::ifstream input(filename);
    output_dir_ = output_dir;
    ++counter_;

    std::vector<int> xcol;
    std::vector<int> ycol;
    std::vector<int> zcol;
    std::vector<int> row_values;
    std::string line_values;

    while(std::getline(input, line)) {
        std::istringstream in(line);
        while (std::getline(in, line_values, ' ')) {
            if ((line_values == "x") || (line_values == "y") || (line_values == "z")) continue;
            row_values.push_back(std::stoi(line_values));
        }
    }

    for (int i = 0; i < row_values.size()/3; ++i) {
        xcol.push_back(row_values[3*i]);
        ycol.push_back(row_values[3*i + 1]);
        zcol.push_back(row_values[3*i + 2]);
    }
    
    res_x_ = *max_element(xcol.begin(), xcol.end()) - *min_element(xcol.begin(), xcol.end()) + 1;
    res_y_ = *max_element(ycol.begin(), ycol.end()) - *min_element(ycol.begin(), ycol.end()) + 1;
    res_z_ = *max_element(zcol.begin(), zcol.end()) - *min_element(zcol.begin(), zcol.end()) + 1;

    domain_x_ = (double)res_x_;
    domain_y_ = (double)res_y_;
    domain_z_ = (double)res_z_;

    dx_ = domain_x_/(double)res_x_;
    dy_ = domain_y_/(double)res_y_;
    dz_ = domain_z_/(double)res_z_;

    grid_.resize(res_x_, std::vector< std::vector<int> >(res_y_, std::vector<int>(res_z_, 0)));
    
    auto x_index = xcol.begin();
    auto y_index = ycol.begin();
    auto z_index = zcol.begin();

    while (x_index != xcol.end() && y_index != ycol.end() && z_index != zcol.end()) {
        if (grid_.at(*x_index).at(*y_index).at(*z_index) == 0) {
            grid_.at(*x_index).at(*y_index).at(*z_index) = 1;
        ++num_solid_;
        }
        ++x_index;
        ++y_index;
        ++z_index;
    } 
}

int Domain3D::nodeType(int x, int y, int z) {
    bool solid = false;
    if (grid_.at(x).at(y).at(z) == 1)
        solid = true;
    int num_adjacent = 0;
    int num_solid = 0;
    for (std::size_t i = 0; i < sizeof(ix_); i++) {
        if (inDomain(x + ix_[i], y + iy_[i], z + iz_[i])) {
            num_adjacent += 1;
            num_solid += grid_.at(x + ix_[i]).at(y + iy_[i]).at(z + iz_[i]);
        }
    }

    if ((solid) && (num_adjacent == num_solid))
        return 0;
    else if ((solid) && (num_solid < num_adjacent))
        return 1;
    else if ((!solid) && (num_solid < num_adjacent) && (num_solid != 0))
        return 2;
    else if ((!solid) && (num_solid == 0))
        return 3;
    else if ((solid) && (num_solid == 0))
        return -1;
    else
        return -2;
}

void Domain3D::gridToCSV(std::string flag) {
    std::string grid_outname = output_dir_ + "/Domain3D_" + flag + '_' + std::to_string(counter_) + ".csv";
    std::ofstream gridout(grid_outname.c_str());
    if (gridout.is_open()) {
        gridout <<"x,y,z "<<std::endl;
        int xindex, yindex, zindex;
        for (row_ = grid_.begin(); row_!= grid_.end(); row_++) {
            xindex = row_ - grid_.begin();
            for (col_ = row_ -> begin(); col_ != row_ -> end(); col_++) {
                yindex = col_ - row_ -> begin();
                for (dep_ = col_ -> begin(); dep_ != col_ -> end(); dep_++) {
                    zindex = dep_ - col_ -> begin();
                    if (nodeType(xindex, yindex, zindex) == node_type[flag])
                        gridout<<(double)xindex*dx_<<","<<(double)yindex*dy_<<","<<(double)zindex*dz_<<std::endl;
                }
            }
        }
    }
}


bool Domain3D::inDomain(int x, int y, int z) {return ((x >= 0) &&
 (x < res_x_) && (y >= 0)&& (y < res_y_) &&
 (z >= 0) && (z < res_z_));}
