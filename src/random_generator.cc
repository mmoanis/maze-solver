#include <random_generator.hpp>
#include <maze.hpp>

#include <iostream>
#include <fstream>
#include <random>
#include <ctime>
#include <set>
//=======================
RandomMazeGenerator::~RandomMazeGenerator()
{

}
//=======================
class DFSRandomMazeGenerator;

class DFSRandomMazeGenerator : public RandomMazeGenerator
{
public:
    virtual ~DFSRandomMazeGenerator()
    {
    }
    virtual bool generate_maze(Maze& maze);
};

bool
DFSRandomMazeGenerator::generate_maze(Maze& maze)
{
    // READ THE GENERATED MAZE FROM THE GENERATOR EXECUTABLE
    std::ifstream fin("maze2.txt", std::ios::in);
    if (!fin) return false;

    unsigned char C;
    int I = 0;
    while (fin >> std::noskipws >> C) {
        if (C != '\n')
        {
            maze[I] = C;
            if (maze[I] == MAZE_TILE_START) maze.Start = I;
            if (maze[I] == MAZE_TILE_END) maze.End = I;
            I++;
        }
    }

    //std::cout << I << std::endl;
    if (I != MAZE_SIZE_ARRAY)
        return false;

    return true;
}
//=======================



std::shared_ptr<RandomMazeGenerator>
RandomMazeGenerator::get_generator(/*RandomMazeGenerator::GeneratorTypes*/)
{
    //return shared_ptr<DFSRandomMazeGenerator> (new DFSRandomMazeGenerator());
    return std::shared_ptr<RandomMazeGenerator> (
                                                 static_cast<RandomMazeGenerator*> (new DFSRandomMazeGenerator())
                                                                );
}
