#pragma once
#include <memory>

class Maze;

class RandomMazeGenerator
{
public:
    //enum GeneratorTypes
    //{
    //    RANDOM_MAZE_GENERATOR_DFS = 0
    //};

    virtual ~RandomMazeGenerator();

    virtual bool generate_maze(Maze& maze) = 0;

    static std::shared_ptr<RandomMazeGenerator> get_generator(/*RandomMazeGenerator::GeneratorTypes*/);
};
