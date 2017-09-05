#pragma once

#include <random_generator.hpp>
#include <solver.hpp>
#include <maze.hpp>
#include <render.hpp>
#include <music.hpp>

#include <memory>

class Application;


class Application
{
public:
    Application() :
        m_mazeGenerator(RandomMazeGenerator::get_generator()),
        m_mazeSolver(MazeSolver::get_solver(MAZE_SOLVER_BFS)),
        m_renderer(new Renderer()), m_mplayer(MPlayer::GetMPlayer())
    {
    }

    int run();

    std::shared_ptr<RandomMazeGenerator> get_generator() const
    {
        return m_mazeGenerator;
    }

    //Maze& get_maze() const
    //{
    //    return m_maze;
    //}

protected:
    std::shared_ptr<RandomMazeGenerator> m_mazeGenerator;
    std::shared_ptr<MazeSolver> m_mazeSolver;
    std::shared_ptr<Renderer> m_renderer;
    MPlayer& m_mplayer;
    Maze m_maze;
};
