# ifndef BALLS_H_
# define BALLS_H_

# include "../include/header.h"
# include "../include/maxball.h"
# include "../include/domain2d.h"
# include "../include/pore.h"

class Domain2D;

class Balls {
    private:
        std::vector<MaxBall> max_balls_;
        std::vector<MaxBall>::iterator balls_it_;
        std::vector<Pore> pores_;
        std::vector<Pore>::iterator pores_it_;
    
    protected:
        std::unordered_map<int, int> ball_pore_index_map_;
        std::vector< std::vector<int> > adjacency_matrix_;
        containers::AdjList adjacency_list_;
        std::string output_dir_;
        int counter_;
        int max_size_;

    public:
        Balls() = default;
        virtual ~Balls() = default;
        void generateBalls(std::unique_ptr<Domain2D>, double);
        void sortBallsRadius();
        void resetBallsIndex();
        void generateBallGroups();
        void populateChildren(int, int);
        void populateSiblings();
        void generateAdjacencyMatrix();
        void generateAdjacencyList();
        void generatePoreConnections();
        void adjacencyMatrixToTXT();
        void adjacencyListToTXT();
        void operator()(std::unique_ptr<Domain2D>, double);
        virtual void ballsToCSV();
        virtual void poresToCSV();
        virtual void generatePores();
};

# endif






