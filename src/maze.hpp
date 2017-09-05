#pragma once

#include <array>
#include <iostream>

#define MAZE_DIM_X 25
#define MAZE_DIM_Y 25
#define MAZE_SIZE_ARRAY MAZE_DIM_X * MAZE_DIM_Y

enum MAZE_TILE_TYPE
{
    MAZE_TILE_BLOCKED = '*',
    MAZE_TILE_PATHABLE = ' ',
    MAZE_TILE_START = 'S',
    MAZE_TILE_END = 'E',
    MAZE_TILE_PATHED = '.'
};

struct Maze
{

    using MazeImpl = std::array<unsigned char, MAZE_SIZE_ARRAY>;
    MazeImpl m_maze;
    MazeImpl::size_type Start, End;

    Maze() {
        m_maze.fill(MAZE_TILE_BLOCKED);
    }

    Maze(const Maze&) = delete;
    Maze& operator=(const Maze&) = delete;


    MazeImpl::value_type& operator[](size_t i)
    {
        return m_maze[i];
    }
    MazeImpl& operator()(void)
    {
        return m_maze;
    }

    const std::pair<int, int> IndexAsPair(const int &i) const
    {
        const int y = (int) (i / MAZE_DIM_X);
		const int x = i - (y * MAZE_DIM_Y);
		//std::cout << x << ' ' << y << ' ' << i << std::endl;
		return std::make_pair(x, y);

    }
    const int PairAsIndex(std::pair<int, int> &p) const
    {
        return p.first + p.second * MAZE_DIM_Y;
    }

    bool ValidIndex(const int &i) const
    {
        return i >= 0 && i < m_maze.size();
    }

    bool ValidPair(const std::pair<int, int> & p) const
    {
        return p.first >= 0 && p.first < MAZE_DIM_X
        && p.second >= 0 && p.second < MAZE_DIM_Y;
    }

    /////
    void print(std::ostream& out)
    {
        for (int i = 0; i < MAZE_DIM_Y; ++i)
        {
            for (int j = 0; j < MAZE_DIM_X; ++j)
            {
                int p = j + MAZE_DIM_Y * i;
                out << m_maze[p];
            }
            out << std::endl;
        }
    }
};
