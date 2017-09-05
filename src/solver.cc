#include <solver.hpp>
#include <maze.hpp>

#include <iostream>
#include <queue>
#include <limits>

//=====================================
class BFSMazeSolver : public MazeSolver
{
public:
    virtual ~BFSMazeSolver()
    {
    }
    virtual bool solve_maze(Maze& maze);
};

bool
BFSMazeSolver::solve_maze(Maze& maze)
{
	std::cout << "BFS MAZE SOLVER STARTING ...\nMAZE START: " << maze.Start <<
	"MAZE END: " << maze.End << std::endl;

	bool reachedEnd = false;
	std::queue<int> BFSQueue;
	BFSQueue.push(maze.Start);
	while (!BFSQueue.empty()) {
		const int nCurrent = BFSQueue.front();
		BFSQueue.pop();

		// convert index to (x,y)
		const std::pair<int, int> pCurrent = maze.IndexAsPair(nCurrent);
		const int nCurrentY = pCurrent.second;
		const int nCurrentX = pCurrent.first;

		// see where we can go from this cell, and update the queue, and the mapInfo
		// (x-1, y) (x, y-1) (x+1, y) (x, y+1)
		std::pair<int, int> nextCells [4] = { {nCurrentX-1, nCurrentY}, {nCurrentX, nCurrentY-1},
		 {nCurrentX+1, nCurrentY}, {nCurrentX, nCurrentY+1} };

		for (int i = 0; i < 4; i++) {
			const int nNext = maze.PairAsIndex(nextCells[i]);
			// explore only valid cells
			if (maze.ValidIndex(nNext)) {
				if (maze[nNext] == MAZE_TILE_PATHABLE) {
					maze[nNext] = MAZE_TILE_PATHED;

					BFSQueue.push(nNext);
				} else if (maze[nNext] == MAZE_TILE_END) {
				    reachedEnd = true;
				    break;
				}
			}
		}

		if (reachedEnd) break;
	}

    return reachedEnd;
}
//=====================================

class DFSMazeSolver : public MazeSolver
{
public:
    virtual ~DFSMazeSolver()
    {
    }
    virtual bool solve_maze(Maze& maze);
};

bool
DFSMazeSolver::solve_maze(Maze& maze)
{
    return false;
}
//=====================================



std::shared_ptr<MazeSolver>
MazeSolver::get_solver(const MazeSolverType& t)
{
    MazeSolver* solverPtr = nullptr;
    switch (t) {
    case MAZE_SOLVER_DFS:
        solverPtr = static_cast<MazeSolver*> (new DFSMazeSolver());
        break;
    default:
        solverPtr = static_cast<MazeSolver*> (new BFSMazeSolver());
        break;
    }
    return std::shared_ptr<MazeSolver>(solverPtr);
}
