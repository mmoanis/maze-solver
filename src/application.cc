#include <application.hpp>

#include <cstdlib>
#include <iostream>


int
Application::run()
{
    std::cout << "GENERATING MAZE WITH DIM: " << MAZE_DIM_X << 'x' << MAZE_DIM_Y << std::endl;
    if (!m_mazeGenerator->generate_maze(m_maze))
    {
        std::cerr << "FAILED TO GENERATE MAZE." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "SUCCESSFULLY GENERATED MAZE:" << std::endl;
    m_maze.print(std::cout);


    std::cout << "STARTING MAZE SOLVER." << std::endl;
    if (!m_mazeSolver->solve_maze(m_maze))
    {
        std::cerr << "FAILED TO SOLVE MAZE." << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "SUCCESSFULLY SOLVED MAZE:" << std::endl;
    m_maze.print(std::cout);

    return EXIT_SUCCESS ;
}
