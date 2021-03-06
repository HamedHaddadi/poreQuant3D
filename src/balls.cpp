# include "../include/balls.h"

void Balls::generateBalls(std::unique_ptr<Domain2D> domain, double threshold) {

    int row, col, this_node{0}, counter{0};
    double dx, dy;
    bool loop_flag = true;
    row = domain -> grid_.size();
    col = domain -> grid_[0].size();
    dx = domain -> dx_;
    dy = domain -> dy_;
    output_dir_ = domain -> output_dir_;
    counter_ = domain -> counter_;
    int range_max = (row >= col) ? row: col;

    for (int cx = 0; cx < row; cx++)
        for (int cy = 0; cy < col; cy++)
        {
            loop_flag = true;
            if ((domain -> nodeType(cx, cy) == 0) ||
                    (domain -> nodeType(cx, cy) == 1) ||
                        (domain -> nodeType(cx, cy) == -1) ||
                             (domain -> nodeType(cx, cy) == -2)) continue;
            for (int radius = 1; radius < range_max && loop_flag; radius++) {
                for (int x = utilities::minRes(cx - radius, 0); x <= utilities::maxRes(cx + radius, row) &&loop_flag; x++)
                    for (int y = utilities::minRes(cy - radius, 0); y <= utilities::maxRes(cy + radius, col) &&loop_flag; y++)
                    if (utilities::Radius(x - cx, y -cy) <= radius) {
                        this_node = domain -> nodeType(x, y);
                        if (((this_node == 0) || (this_node == 1)) && radius > 1)
                        {
                            loop_flag = false;
                            max_balls_.emplace_back(std::make_tuple((double)cx*dx, (double)cy*dy), counter,\
                            utilities::Radius((double)(x - cx)*dx, (double)(y -cy)*dy), threshold);
                            ++counter;
                        }
                    }
            }
        }
max_size_ = max_balls_.size();
}
    
void Balls::sortBallsRadius() {
    std::sort(max_balls_.begin(), max_balls_.end(), [] (const MaxBall & lhs, const MaxBall & rhs){
        return (lhs.getRadius() > rhs.getRadius());
    });
    resetBallsIndex();
}

void Balls::resetBallsIndex() {
    for (balls_it_ = max_balls_.begin(); balls_it_ != max_balls_.end(); ++balls_it_)
        balls_it_ -> setID(std::distance(max_balls_.begin(), balls_it_));
}

void Balls::generateBallGroups() {
    for (int i = 0; i < max_size_ - 1; i++)
        for (int j = i + 1; j < max_size_; j++) {
            if (max_balls_.at(j).fullyIncludedIn(max_balls_.at(i))) {
                max_balls_.at(j).makeIncluded();
                max_balls_.at(j).raiseRank();
            }
            else if (max_balls_.at(i).overlapsWith(max_balls_.at(j))) {
                max_balls_.at(j).raiseRank();
                max_balls_.at(j).addToParents(max_balls_.at(i));
                populateChildren(i,j);
            }
        }
}

void Balls::populateChildren(int i, int j) {
    // NOTE: else can be commented out if direct children of parents
    // are intended
    if (max_balls_.at(i).getRank() == 0)
        max_balls_.at(i).addToChildren(j);
    else 
     for (auto & parent: max_balls_.at(i).getParents())
         max_balls_.at(parent).addToChildren(j);
    
}

void Balls::populateSiblings() {
    // parents of a child are siblings
    std::set<int> key_parents;
    for (balls_it_ = max_balls_.begin(); balls_it_ != max_balls_.end(); ++balls_it_) {
        if (balls_it_ -> getRank() > 0) {
            key_parents = balls_it_ -> getParents();
            for (const auto & parent:key_parents) {
                max_balls_.at(parent).addToSiblings(key_parents);
            }
        }
    }
}

void Balls::generatePores() {
    int pore_count{0};
    std::set<int> connections;
    std::vector<containers::Tuple3D<double> > pore_family;
    std::tuple<double, double> parent_coordinates, child_coordinates;
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
            pore_family.emplace_back(std::make_tuple(std::get<0>(parent_coordinates),
                 std::get<1>(parent_coordinates),
                     radius));
            
            for (auto & child:balls_it_ -> getChildren()) {
                child_coordinates = max_balls_.at(child).getCoordinates();
                pore_family.emplace_back(std::make_tuple(std::get<0>(child_coordinates),
                     std::get<1>(child_coordinates),
                      max_balls_.at(child).getRadius()));
            }
            pores_.emplace_back(parent_coordinates, pore_count, radius, connections, pore_family);
            ++pore_count;
        }
    }
}

void Balls::generatePoreConnections() {
    std::set<int> temp_connections, connections;
    for (pores_it_ = pores_.begin(); pores_it_ != pores_.end(); ++pores_it_) {
        temp_connections.clear();
        connections = pores_it_ -> getConnections();
        for (auto & connection:connections) 
            temp_connections.insert(ball_pore_index_map_[connection]);
        pores_it_ -> setConnections(temp_connections);
    }
}

void Balls::generateAdjacencyMatrix() {
    int pore_size = pores_.size();
    adjacency_matrix_.resize(pore_size, std::vector<int>(pore_size, 0));

    std::set<int> connections;
    std::set<int>::iterator con_it;
    int pore_id;
    for (pores_it_ = pores_.begin(); pores_it_ != pores_.end(); pores_it_++) {
        connections = pores_it_ -> getConnections();
        pore_id = pores_it_ -> getID();
        adjacency_matrix_.at(pore_id).at(pore_id) = 1;
        for (con_it = connections.begin(); con_it != connections.end(); con_it++) {
            adjacency_matrix_.at(pore_id).at(*con_it) = 1;
            adjacency_matrix_.at(*con_it).at(pore_id) = 1;
        }
    }
}

void Balls::generateAdjacencyList() {
    for (pores_it_ = pores_.begin(); pores_it_ != pores_.end(); pores_it_++) {
        adjacency_list_.insertNode(pores_it_ -> getID(), pores_it_ -> getConnections());
    }
}


/* output methods */
void Balls::ballsToCSV() {
    
    std::string out_filename = output_dir_ + "/maxball_" + std::to_string(counter_) + ".csv";
    std::ofstream balls_out(out_filename.c_str());
    if (!balls_out.is_open())
        std::cout <<"could not open the file in ballstocsv"<<std::endl;

    balls_out <<"x,y,radius,rank"<< std::endl;
    for (auto const & ball:max_balls_) {
        balls_out<<ball<<std::endl;
    }
}

void Balls::poresToCSV() {

    std::string pore_filename = output_dir_ + "/pores_" + std::to_string(counter_) + ".csv";
    std::string family_dirname = output_dir_ + "/Pore_Families_of_Plane_" + std::to_string(counter_);
    utilities::makedir(family_dirname);

    std::ofstream pores_out(pore_filename);
    if (!pores_out.is_open()) {
        std::cout <<"did not open pore family output file" <<std::endl;
    }

    pores_out <<"id,x,y,radius"<<std::endl;
    for (auto const & pore:pores_) {
        pores_out<<pore<<std::endl;
        std::string family_filename = family_dirname + "/family_of_pore_" + std::to_string(pores_it_ -> getID()) + ".csv";
        std::ofstream family_out(family_filename);
        if (!family_out.is_open()) {
            std::cout <<"could not open file for family output"<<std::endl;
        }        
        for (auto const & member:pore.getPoreFamily())
            family_out<<member<<std::endl;
    }
}

void Balls::adjacencyMatrixToTXT() {
    std::string out_filename = output_dir_ + "/connections_" + std::to_string(counter_) + ".txt";
    std::ofstream adjacency_out(out_filename.c_str());
    if (!adjacency_out.is_open())
        std::cout <<"could not open adjacency output file" <<std::endl;
    
    for (std::vector< std::vector<int> >::iterator row = adjacency_matrix_.begin(); row != adjacency_matrix_.end(); row++) {
        for (std::vector<int>::iterator col = row -> begin(); col != row -> end(); col++) {
            adjacency_out<<*col<<" ";
            if (col == std::prev(row -> end()))
                adjacency_out<<std::endl;
        }
    }
}

void Balls::adjacencyListToTXT() {
    std::string out_filename = output_dir_ + "/adjacency_list_" + std::to_string(counter_) + ".dat";
    std::ofstream list_out(out_filename.c_str());
    if (!list_out.is_open())
        std::cout <<"could not open adjacency output file" <<std::endl; 
    list_out << adjacency_list_;   

}


void Balls::operator()(std::unique_ptr<Domain2D> domain, double threshold) {
    generateBalls(std::move(domain), threshold);
    sortBallsRadius();
    generateBallGroups();
    populateSiblings();
    generatePores();
    generatePoreConnections();
    generateAdjacencyMatrix();
    generateAdjacencyList();
    ballsToCSV();
    poresToCSV();
    adjacencyMatrixToTXT();
    adjacencyListToTXT();
}