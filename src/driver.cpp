
# include "header.h"
# include "domain2d.h"
# include "balls.h"

void driver(std::string file_name, std::string output_dir) {

    std::cout <<"the file name is "<<file_name<<std::endl;

    Balls balls;
    Domain2D domain(file_name, output_dir);
    domain.gridToCSV("void");
    balls.generateBalls(domain);
    std::cout <<"balls generated "<<std::endl;
    balls.ballsToCSV();
    balls.sortBallsRadius();
    balls.generateBallGroups();
    std::cout <<"ball groups generated "<<std::endl;
    balls.populateSiblings();
    balls.generatePores();
    balls.generatePoreConnections();
    balls.generatePoreAdjacency();
    balls.adjacencyToTXT();
}
