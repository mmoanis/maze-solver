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
    MAZE_TILE_PATHED = 'x',
    MAZE_TILE_EXPLORED = '.'
};

struct MazeCoord
{
    int X;
    int Y;

    MazeCoord(int x, int y) : X(x), Y(y) {}

    friend std::ostream& operator<<(const std::ostream& out, const MazeCoord& coord);
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

    MazeCoord IndexAsCoord(const int &i) const
    {
        const int y = (int) (i / MAZE_DIM_X);
		const int x = i - (y * MAZE_DIM_Y);
		return {x, y};

    }
    const int CoordAsIndex(const MazeCoord &p) const
    {
        return p.X + p.Y * MAZE_DIM_Y;
    }

    bool ValidIndex(const int &i) const
    {
        return i >= 0 && i < m_maze.size();
    }

    bool ValidCoord(const MazeCoord & p) const
    {
        return p.X >= 0 && p.X < MAZE_DIM_X
        && p.Y >= 0 && p.Y < MAZE_DIM_Y;
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

inline std::ostream& operator<<(std::ostream& out, const MazeCoord &coord)
{
    out << '(' << coord.X << ',' << coord.Y <<  ')';
    return out;
}

