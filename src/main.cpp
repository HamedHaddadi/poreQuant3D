
# include "../include/utilities.h"
# include "../include/domain2d.h"
# include "../include/balls.h"
# include "../include/domain3d.h"
# include "../include/balls3d.h"
# include <iostream>
# include <string>
# include <vector>
# include <numeric>
# include <cstdlib>
# include <stdexcept>
# include <chrono>

int main (int argc, char * argv[]) {

    std::vector<std::string> image_files;
    std::string dimension_flag(argv[1]);
    std::string image_dir(argv[2]);
    std::string save_dir;
    std::string output_dir;
    double threshold{0.0};
    std::vector<double> run_times;

    if (argc > 3) {
        save_dir = argv[3];
        if (save_dir.rfind("/", 0) != 0) {
            save_dir = "/" + save_dir;
            output_dir = image_dir + save_dir;
        }
        if (argc >= 4) {
            threshold = std::stod(argv[4]);
            output_dir = image_dir + save_dir + argv[4];
        }
    }
    else if (argc == 3) 
        output_dir = image_dir + "/Pore_Analytics_Outputs";
    
    utilities::makedir(output_dir);
    
    if (image_dir.find("/*") == std::string::npos)
        image_dir += "/*";
    
    utilities::listdir(image_files, image_dir);
    
 
    if (dimension_flag == "2") {
        std::cout <<" starting a 2d analysis ... "<<std::endl;
        for (std::vector< std::string >::iterator file_it = image_files.begin(); file_it != image_files.end(); ++file_it) {
            auto start = std::chrono::high_resolution_clock::now();
            Balls balls;
            auto domain = std::make_unique<Domain2D>(*file_it, output_dir);
            balls(std::move(domain), threshold);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_delta = end - start;
            run_times.push_back(time_delta.count());
        }        
    }

    else if (dimension_flag == "3") {
        for (std::vector< std::string >::iterator file_it = image_files.begin(); file_it != image_files.end(); ++file_it) {
            auto start = std::chrono::high_resolution_clock::now();    
            Balls3D balls;
            auto domain = std::make_unique<Domain3D>(*file_it, output_dir);
            balls(std::move(domain), threshold);
            auto end = std::chrono::high_resolution_clock::now();
            std::chrono::duration<double> time_delta = end - start;
            run_times.push_back(time_delta.count());
        }
    }
    
    else {
        std::cout <<"run the program with a valid dimension flag: 2 or 3"<<std::endl;
    }

    // get some report on the screen 
    auto const count = static_cast<double>(run_times.size());
    auto total_time = std::accumulate(run_times.begin(), run_times.end(), 0.0);
    std::cout <<" the total run time for each image entry was ... "<< total_time<<" seconds. "<<std::endl;
    std::cout <<"each image took about "<< total_time/count<<" seconds to process ..."<<std::endl;
    
    return 0;

}

