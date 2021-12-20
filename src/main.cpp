
# include "utilities.h"
# include "domain2d.h"
# include "balls.h"
# include "domain3d.h"
# include "balls3d.h"
# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <stdexcept>


int main (int argc, char * argv[]) {

    std::vector<std::string> image_files;
    std::string dimension_flag(argv[1]);
    std::string image_dir(argv[2]);
    std::string save_dir;
    std::string output_dir;

    std::cout <<"dimension flag is "<< dimension_flag <<std::endl;

    if (argc > 3) {
        save_dir = argv[3];
        if (save_dir.rfind("/", 0) != 0) {
            save_dir = "/" + save_dir;
            output_dir = image_dir + save_dir;
        }
    }
    else if (argc == 3) 
        output_dir = image_dir + "/Pore_Analytics_Outputs";
    
    utilities::makedir(output_dir);
    
    if (image_dir.find("/*") == std::string::npos)
        image_dir += "/*";
    
    utilities::listdir(image_files, image_dir);
        
    if (dimension_flag == "2") {
        for (std::vector< std::string >::iterator file_it = image_files.begin(); file_it != image_files.end(); ++file_it) {
            Balls balls;
            Domain2D domain(*file_it, output_dir);
            balls(domain);
        }        
    }

    else if (dimension_flag == "3") {
        for (std::vector< std::string >::iterator file_it = image_files.begin(); file_it != image_files.end(); ++file_it) {
            Balls3D balls;
            Domain3D domain(*file_it, output_dir);
            balls(domain);
        }
    }
    
    else {
        std::cout <<"run the program with a valid dimension flag: 2 or 3"<<std::endl;
    }
    
    return 0;

}

