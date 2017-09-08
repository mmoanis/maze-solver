#include <solver.hpp>
#include <maze.hpp>

#include <iostream>
#include <queue>
#include <vector>
#include <cmath>
#include <limits>

void
MazeSolver::init(const Maze& maze)
{
    std::cout << m_name << " MAZE SOLVER STARTING ...\nMAZE START: " << maze.IndexAsCoord(maze.Start) <<
	"MAZE END: " << maze.IndexAsCoord(maze.End) << std::endl;
}

//=====================================
class BFSMazeSolver : public MazeSolver
{
public:
    BFSMazeSolver() : MazeSolver(MAZE_SOLVER_BFS, "BFS") {}
    virtual ~BFSMazeSolver(){}
    virtual bool solve_maze(Maze& maze);
};

bool
BFSMazeSolver::solve_maze(Maze& maze)
{
	bool reachedEnd = false;
	std::queue<int> BFSQueue;
	BFSQueue.push(maze.Start);
	while (!BFSQueue.empty()) {
		const int nCurrent = BFSQueue.front();
		BFSQueue.pop();

		// convert index to (x,y)
		const MazeCoord pCurrent = maze.IndexAsCoord(nCurrent);
		const int nCurrentY = pCurrent.Y;
		const int nCurrentX = pCurrent.X;

		maze[nCurrent] = MAZE_TILE_PATHED;

		// see where we can go from this cell, and update the queue, and the mapInfo
		// (x-1, y) (x, y-1) (x+1, y) (x, y+1)
		MazeCoord nextCells [4] = { {nCurrentX-1, nCurrentY}, {nCurrentX, nCurrentY-1},
		 {nCurrentX+1, nCurrentY}, {nCurrentX, nCurrentY+1} };

		for (int i = 0; i < 4; i++) {
			const int nNext = maze.CoordAsIndex(nextCells[i]);
			// explore only valid cells
			if (maze.ValidIndex(nNext)) {
				if (maze[nNext] == MAZE_TILE_PATHABLE) {
					maze[nNext] = MAZE_TILE_EXPLORED;

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
    DFSMazeSolver() : MazeSolver(MAZE_SOLVER_DFS, "DFS") {}
    virtual ~DFSMazeSolver() {}
    virtual bool solve_maze(Maze& maze);
};

bool
DFSMazeSolver::solve_maze(Maze& maze)
{
    return false;
}
//=====================================
class GreedyMazeSolver : public MazeSolver
{
public:
    GreedyMazeSolver() : MazeSolver(MAZE_SOLVER_GREEDY, "GREEDY") {}
    virtual ~GreedyMazeSolver() {}
    virtual bool solve_maze(Maze& maze);
protected:
    GreedyMazeSolver(MazeSolverType type, const std::string& name) : MazeSolver(type, name) {}

    virtual double CostFunction(const Maze& maze, const MazeCoord& coord);
};

bool
GreedyMazeSolver::solve_maze(Maze& maze)
{
	using GreedyP = std::pair<int, double>;
	struct ComptGreedy {
	bool operator()(const GreedyP& f, const GreedyP& s) { return f.second > s.second; }
	};
	bool reachedEnd = false;
	std::priority_queue<GreedyP, std::vector<GreedyP>, ComptGreedy> GPQ;
    GPQ.push(std::make_pair(maze.Start, 0.));
    while (!GPQ.empty()) {
        GreedyP p = GPQ.top();
        GPQ.pop();

        // convert index to (x,y)
        const int nCurrent = p.first;
        maze[nCurrent] = MAZE_TILE_PATHED;

		const MazeCoord pCurrent = maze.IndexAsCoord(nCurrent);
		const int nCurrentY = pCurrent.Y;
		const int nCurrentX = pCurrent.X;

		// see where we can go from this cell, and update the queue, and the mapInfo
		// (x-1, y) (x, y-1) (x+1, y) (x, y+1)
		const MazeCoord nextCells [4] = { {nCurrentX-1, nCurrentY}, {nCurrentX, nCurrentY-1},
		 {nCurrentX+1, nCurrentY}, {nCurrentX, nCurrentY+1} };

		for (int i = 0; i < 4; i++) {
			const int nNext = maze.CoordAsIndex(nextCells[i]);
			// explore only valid cells
			if (maze.ValidIndex(nNext)) {
				if (maze[nNext] == MAZE_TILE_PATHABLE) {
					maze[nNext] = MAZE_TILE_EXPLORED;
					double cost = CostFunction(maze, nextCells[i]);
					//std::cout << "\tNeigbours: " << nextCells[i].first << ' ' << nextCells[i].second << ' ' << dis << std::endl;
					GPQ.push(std::make_pair(nNext, cost));
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

double
GreedyMazeSolver::CostFunction(const Maze& maze, const MazeCoord& coord)
{
    static struct EcludiandDistance{
	    double operator() (const MazeCoord &F, const MazeCoord &S)
	    {
	        return //std::sqrt(
                        std::abs  ((S.X-F.X))
                          +
                         std::abs ((S.Y-F.Y))
                         // )
                         ;
	    }
	} EDCalc;

	return EDCalc(coord, maze.IndexAsCoord(maze.End));
}


std::shared_ptr<MazeSolver>
MazeSolver::get_solver(const MazeSolverType& t)
{
    switch (t) {
    case MAZE_SOLVER_DFS:
        return std::static_pointer_cast<MazeSolver> (std::make_shared<DFSMazeSolver> ());
    case MAZE_SOLVER_GREEDY:
        return std::static_pointer_cast<MazeSolver> (std::make_shared<GreedyMazeSolver> ());
    default:
        return std::static_pointer_cast<MazeSolver> (std::make_shared<BFSMazeSolver> ());
    }
}
