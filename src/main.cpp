
# include "utilities.h"
# include "domain2d.h"
# include "balls.h"
# include <iostream>
# include <string>
# include <vector>
# include <cstdlib>
# include <stdexcept>


int main (int argc, char * argv[]) {

    std::vector<std::string> image_files;
    std::string image_dir(argv[1]);
    std::string save_dir;
    std::string output_dir;

    if (argc > 2) {
        save_dir = argv[2];
        if (save_dir.rfind("/", 0) != 0) {
            save_dir = "/" + save_dir;
            output_dir = image_dir + save_dir;
        }
    }
    else if (argc == 2) 
        output_dir = image_dir + "/Pore_Analytics_Outputs";
    
    utilities::makedir(output_dir);
    
    if (image_dir.find("/*") == std::string::npos)
        image_dir += "/*";
    
    utilities::listdir(image_files, image_dir);
    
    for (std::vector< std::string >::iterator file_it = image_files.begin(); file_it != image_files.end(); ++file_it) {
        Balls balls;
        Domain2D domain(*file_it, output_dir);
        balls(domain);
    }

    return 0;

}

