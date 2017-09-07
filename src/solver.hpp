#pragma once

#include <memory>
#include <string>

class Maze;
class MazeSolver;

enum MazeSolverType
{
    MAZE_SOLVER_BFS = 0,
    MAZE_SOLVER_DFS,
    MAZE_SOLVER_GREEDY
};

class MazeSolver
{
public:
    MazeSolver(const MazeSolverType& type, const std::string& name) : m_type(type), m_name(name) {}
    virtual ~MazeSolver() {}
    void init(const Maze& maze);
    virtual bool solve_maze(Maze& maze) = 0;

    static std::shared_ptr<MazeSolver> get_solver(const MazeSolverType&);
protected:
    const MazeSolverType m_type;
    const std::string m_name;
};
