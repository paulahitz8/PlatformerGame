#ifndef __PATHFINDING_H__
#define __PATHFINDING_H__

#include "Module.h"

#include "Point.h"
#include "DynArray.h"
#include "List.h"
#include <unordered_map>
#include "NodeAstar.h"
#include <queue> 

using namespace std;

class PathFinding : public Module
{
public:

	PathFinding();

	// Destructor
	~PathFinding();

	int Heuristic(iPoint, iPoint);
	iPoint Path(iPoint, int);
	iPoint NextMove(NodeAstar*, iPoint);

	bool isVisited(iPoint, List<NodeAstar*>);

	priority_queue<NodeAstar*> UpdateNeighbours(std::priority_queue<NodeAstar*>, iPoint, int, NodeAstar*, NodeAstar*, List<NodeAstar*>);

private:

};

#endif // __PATHFINDING_H__