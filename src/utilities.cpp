# include "../include/utilities.h"

void utilities::makedir(std::string dirname) {
    std::string command = "mkdir " + dirname;
    int status = std::system(command.c_str());
    if (status != 0)
        std::cout <<"could not create directory ..."<< dirname<< std::endl;
}


void utilities::listdir(std::vector<std::string> & file_list, std::string dir_name) {
    glob_t results;
    glob(dir_name.c_str(), GLOB_TILDE, NULL, &results);
    for (unsigned int i = 0; i < results.gl_pathc; ++i) {
        std::string filename(results.gl_pathv[i]);
        if (filename.find(".csv") != std::string::npos)
            file_list.push_back(filename);
    }
    globfree(&results);
}

int utilities::minRes(int coord, int min_coord) {return (coord < min_coord) ? min_coord: coord; }
int utilities::maxRes(int coord, int max_coord) {return (coord >= max_coord) ? max_coord - 1: coord;}

