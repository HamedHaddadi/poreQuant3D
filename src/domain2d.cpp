
# include "../include/domain2d.h"

const int Domain2D::ix_[8] = {1,1,0,-1,-1,-1,0,1};
const int Domain2D::iy_[8] = {0,1,1,1,0,-1,-1,-1};
int Domain2D::counter_{0};

Domain2D::Domain2D(std::string filename, std::string output_dir) {

    std::string line;
    std::ifstream input(filename);
    output_dir_ = output_dir;
    ++counter_;

    std::vector<int> xcol;
    std::vector<int> ycol;
    std::vector<int> row_values;
    std::string line_values;

    while(std::getline(input, line)) {
        std::istringstream in(line);
        while (std::getline(in, line_values, ' ')) {
            if ((line_values == "x") || (line_values == "y") || (line_values == "z")) continue;
            row_values.push_back(std::stoi(line_values));
        }
    }

    int size = row_values.size()/2;
    for (int i = 0; i < size; ++i) {
        xcol.push_back(row_values[2*i]);
        ycol.push_back(row_values[2*i + 1]);
    }
    
    res_x_ = *max_element(xcol.begin(), xcol.end()) - *min_element(xcol.begin(), xcol.end()) + 1;
    res_y_ = *max_element(ycol.begin(), ycol.end()) - *min_element(ycol.begin(), ycol.end()) + 1;

    domain_x_ = (double)res_x_;
    domain_y_ = (double)res_y_;

    dx_ = domain_x_/(double)res_x_;
    dy_ = domain_y_/(double)res_y_;

    grid_.resize(res_x_, std::vector<int>(res_y_, 0));
    
    auto x_index = xcol.begin();
    auto y_index = ycol.begin();

    while (x_index != xcol.end() && y_index != ycol.end()) {
        if (grid_.at(*x_index).at(*y_index) == 0) {
            grid_.at(*x_index).at(*y_index) = 1;
            ++num_solid_;
        }
        ++x_index;
        ++y_index;
    } 
}

int Domain2D::nodeType(int x, int y) {
    bool solid = false;
    if (grid_.at(x).at(y) == 1)
        solid = true;
    int num_adjacent = 0;
    int num_solid = 0;
    for (std::size_t i = 0; i < sizeof(ix_); i++) {
        if (inDomain(x + ix_[i], y + iy_[i])) {
            num_adjacent += 1;
            num_solid += grid_[x + ix_[i]][y + iy_[i]];
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

void Domain2D::gridToCSV(std::string flag) {
    std::string grid_outname = output_dir_ + "/Domain2D_" + flag + '_' + std::to_string(counter_) + ".csv";
    std::ofstream gridout(grid_outname.c_str());
    if (gridout.is_open()) {
        gridout <<"x,y "<<std::endl;
        int xindex, yindex;
        for (row_ = grid_.begin(); row_!= grid_.end(); row_++) {
            xindex = row_ - grid_.begin();
            for (col_ = row_ -> begin(); col_ != row_ -> end(); col_++) {
                yindex = col_ - row_ -> begin();
                if (nodeType(xindex, yindex) == node_type[flag])
                    gridout<<(double)xindex*dx_<<","<<(double)yindex*dy_<<std::endl;
            }
        }
    }
}


/* non static helpers */
bool Domain2D::inDomain(int x, int y) {return ((x >= 0) && (x < res_x_) && (y >= 0)&& (y < res_y_));}


