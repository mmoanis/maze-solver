#include <solver.hpp>
#include <maze.hpp>

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
    //struct MapInfo {
	//	int parent;		// previous index in shortest path to me
	//	//bool visited;	// shortest path from source to me
	//	MapInfo() : parent(-1), distance(std::numeric_limits<int>::max()) {}
	//} * mapInfo = new MapInfo[MAZE_SIZE_ARRAY];

	//mapInfo[maze.Start].parent = maze.Start;
	//mapInfo[maze.Start].distance = 0;

	std::queue<int> BFSQueue;
	BFSQueue.push(maze.Start);
	while (!BFSQueue.empty()) {
		const int nCurrent = BFSQueue.front();
		BFSQueue.pop();

		if (nCurrent == maze.End) break; // Gotcha ...

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
				// this will be false only if this cell was visited before, since we are in an unweighted graph
				if (maze[nNext] == MAZE_TILE_PATHABLE) {
					// update the shortest path
					//mapInfo[nNext].distance = mapInfo[nCurrent].distance + 1;
					//mapInfo[nNext].parent   = nCurrent;
					maze[nNext] = MAZE_TILE_PATHED;

					BFSQueue.push(nNext);
				}
			}
		}
	}
	//// *** Path Finding ends

	//// prepare output
	//bool status = mapInfo[maze.End].distance != std::numeric_limits<int>::max();	// get the path distance
	/*if (status) {
		int walker = maze.End;
		walker = mapInfo[walker].parent;
		// write the shortest path
		while (walker != maze.Start) {
			maze[walker] = MAZE_TILE_PATHED;
			walker = mapInfo[walker].parent;
		}
	}*/

	// keep it clean and shinny
	//delete[] mapInfo;

    return true;
}
//=====================================

MazeSolver::~MazeSolver()
{
}

std::shared_ptr<MazeSolver>
MazeSolver::get_solver(MazeSolverType)
{
    return std::shared_ptr<MazeSolver>
    (static_cast<MazeSolver*> (new BFSMazeSolver()));
}
