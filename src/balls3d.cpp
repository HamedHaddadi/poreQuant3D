
# include "balls3d.h"

void Balls3D::generateBalls(Domain3D & domain) {

    int row, col, dep, node_type{0}, counter{0};
    double dx, dy, dz;
    bool loop_flag = true;
    row = domain.grid_.size();
    col = domain.grid_[0].size();
    dep = domain.grid_[0][0].size();
    dx = domain.dx_;
    dy = domain.dy_;
    dz = domain.dz_;
    output_dir_ = domain.output_dir_;
    counter_ = domain.counter_;

    int range_max = ((row > col) ? row:col);
    range_max = ((range_max > dep) ? range_max:dep);

    for (int cx = 0; cx < row; cx++) {
        for (int cy = 0; cy < col; cy++) {
            for (int cz = 0; cz < dep; cz++) {
                loop_flag = true; 
                if ((domain.nodeType(cx, cy, cz) == 0) || (domain.nodeType(cx, cy, cz) == 1)) continue;
                for (int radius = 1; radius < range_max && loop_flag; radius++) {
                    for (int x = utilities::minRes(cx - radius, 0); x <= utilities::maxRes(cx + radius, row) &&loop_flag; x++)
                        for (int y = utilities::minRes(cy - radius, 0); y <= utilities::maxRes(cy + radius, row) &&loop_flag; y++)
                            for (int z = utilities::minRes(cz - radius, 0); z <= utilities::maxRes(cz + radius, dep) && loop_flag; z++) {
                                if (utilities::Radius3D<int>(x - cx, y - cy, z - cz) <= radius) {
                                    node_type = domain.nodeType(x, y, z);
                                    if ((node_type == 0) || (node_type == 1)) {
                                        loop_flag = false;
                                        max_balls_.emplace_back(std::make_tuple((double)cx*dx, (double)cy*dy, (double)cz*dz), 
                                                        counter, utilities::Radius3D<double>((double)(x - cx)*dx, (double)(y - cy)*dy, (double)(z - cz)*dz));
                                        ++counter;
                                    }
                                }
                            }    
                }
            }
        }
    }
    max_size_ = max_balls_.size();
    
}

void Balls3D::generatePores() {

    int pore_count{0};
    std::set<int> connections;
    std::vector<std::tuple<double, double, double, double> > pore_family;
    std::tuple<double, double, double> parent_coordinates, child_coordinates;
    double radius;

    for (balls_it_ = max_balls_.begin(); balls_it_ != max_balls_.end(); balls_it_++) {
        if (balls_it_ -> getRank() == 0) {
            ball_pore_index_map_[balls_it_ -> getID()] = pore_count;
            
            connections.clear();
            for (auto const & connection:balls_it_ -> getSiblings())
                if (max_balls_.at(connection).getRank() == 0)
                    connections.insert(connection);
            
            pore_family.clear();
            parent_coordinates = balls_it_ -> getCoordinates();
            radius = balls_it_ -> getRadius();
            pore_family.emplace_back(std::get<0>(parent_coordinates), std::get<1>(parent_coordinates), std::get<2>(parent_coordinates), radius);
            
            for (auto & child:balls_it_ -> getChildren()) {
                child_coordinates = max_balls_.at(child).getCoordinates();
                pore_family.emplace_back(std::get<0>(child_coordinates), std::get<1>(child_coordinates), std::get<2>(child_coordinates), max_balls_.at(child).getRadius());
            }
            pores_.emplace_back(parent_coordinates, pore_count, radius, connections, pore_family);
            ++pore_count;
        }
    }  

}

/* output methods */
void Balls3D::ballsToCSV() {
    
    std::string out_filename = output_dir_ + "/maxball_" + std::to_string(counter_) + ".csv";
    std::ofstream balls_out(out_filename.c_str());
    if (!balls_out.is_open())
        std::cout <<"could not open the file in ballstocsv"<<std::endl;

    balls_out <<"x,y,z,radius,rank"<< std::endl;
    for (balls_it_ = max_balls_.begin(); balls_it_ != max_balls_.end(); balls_it_++) {
        auto coordinates = balls_it_ -> getCoordinates();
        balls_out<<std::get<0>(coordinates)<<","
            <<std::get<1>(coordinates)<<","
                <<std::get<2>(coordinates)<<","
                    <<balls_it_ -> getRadius()<<","
                        <<balls_it_ -> getRank()<<std::endl;
    }
}


void Balls3D::poresToCSV() {

    std::string pore_filename = output_dir_ + "/pores_" + std::to_string(counter_) + ".csv";
    std::string family_dirname = output_dir_ + "/Pore_Families_of_Plane_" + std::to_string(counter_);
    utilities::makedir(family_dirname);

    std::ofstream pores_out(pore_filename);
    if (!pores_out.is_open()) {
        std::cout <<"did not open pore family output file" <<std::endl;
    }

    pores_out <<"id,x,y,z,radius"<<std::endl;
    for (pores_it_ = pores_.begin(); pores_it_ != pores_.end(); ++pores_it_) {
        auto coordinates = pores_it_ -> getCoordinates();
        pores_out<<pores_it_ -> getID()<<","<<
            std::get<0>(coordinates)<<","<<
                std::get<1>(coordinates)<<","<<
                    std::get<2>(coordinates)<<","<<
                        pores_it_ -> getRadius()<<std::endl;
        // output pore families
        std::string family_filename = family_dirname + "/family_of_pore_" + std::to_string(pores_it_ -> getID()) + ".csv";
        std::ofstream family_out(family_filename);
        if (!family_out.is_open()) {
            std::cout <<"could not open file for family output"<<std::endl;
        }
        for (auto & member:pores_it_ -> getPoreFamily()) 
            family_out<<std::get<0>(member)<<","<<std::get<1>(member)<<","<<std::get<2>(member)<<","<<std::get<3>(member)<<std::endl;
        
    }
}


