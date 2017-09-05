#pragma once

#include <memory>

class Maze;
class MazeSolver;

enum MazeSolverType
{
    MAZE_SOLVER_BFS = 0,
    MAZE_SOLVER_DFS
};

class MazeSolver
{
public:
    virtual ~MazeSolver() {}
    virtual bool solve_maze(Maze& maze) = 0;

    static std::shared_ptr<MazeSolver> get_solver(const MazeSolverType&);
};
