#include "App.h"
#include "PathFinding.h"
#include "Player.h"
#include "List.h"
#include "NodeAstar.h"
#include <unordered_map>
#include <queue> 

#include "Defs.h"
#include "Log.h"

using namespace std; 

PathFinding::PathFinding() : Module()
{
	name.Create("pathfinding");
}

// Destructor
PathFinding::~PathFinding()
{
	//RELEASE_ARRAY(map);
}

//bool PathFinding::CleanUp()
//{
//	LOG("Freeing pathfinding library");
//
//	lastPath.Clear();
//	RELEASE_ARRAY(map);
//
//	return true;
//}

//// Sets up the walkability map
//void PathFinding::SetMap(uint width, uint height, uchar* data)
//{
//	this->width = width;
//	this->height = height;
//
//	RELEASE_ARRAY(map);
//	map = new uchar[width * height];
//	memcpy(map, data, width * height);
//}
//
//// Utility: return true if pos is inside the map boundaries
//bool PathFinding::CheckBoundaries(const iPoint& pos) const
//{
//	return (pos.x >= 0 && pos.x <= (int)width &&
//		pos.y >= 0 && pos.y <= (int)height);
//}
//
//// Utility: returns true is the tile is walkable
//bool PathFinding::IsWalkable(const iPoint& pos) const
//{
//	uchar t = GetTileAt(pos);
//	return t != INVALID_WALK_CODE && t > 0;
//}
//
//// Utility: return the walkability value of a tile
//uchar PathFinding::GetTileAt(const iPoint& pos) const
//{
//	if (CheckBoundaries(pos))
//		return map[(pos.y * width) + pos.x];
//
//	return INVALID_WALK_CODE;
//}
//
//// To request all tiles involved in the last generated path
//const DynArray<iPoint>* PathFinding::GetLastPath() const
//{
//	return &lastPath;
//}

//// PathList ------------------------------------------------------------------------
//// Looks for a node in this list and returns it's list node or NULL
//// ---------------------------------------------------------------------------------
//const ListItem<PathNode>* PathList::Find(const iPoint& point) const
//{
//	ListItem<PathNode>* item = list.start;
//	while (item)
//	{
//		if (item->data.pos == point)
//			return item;
//		item = item->next;
//	}
//	return NULL;
//}
//
//// PathList ------------------------------------------------------------------------
//// Returns the Pathnode with lowest score in this list or NULL if empty
//// ---------------------------------------------------------------------------------
//ListItem<PathNode>* PathList::GetNodeLowestScore() const
//{
//	ListItem<PathNode>* ret = NULL;
//	int min = 65535;
//
//	ListItem<PathNode>* item = list.end;
//	while (item)
//	{
//		if (item->data.Score() < min)
//		{
//			min = item->data.Score();
//			ret = item;
//		}
//		item = item->prev;
//	}
//	return ret;
//}
//
//// PathNode -------------------------------------------------------------------------
//// Convenient constructors
//// ----------------------------------------------------------------------------------
//PathNode::PathNode() : g(-1), h(-1), pos(-1, -1), parent(NULL)
//{}
//
//PathNode::PathNode(int g, int h, const iPoint& pos, const PathNode* parent) : g(g), h(h), pos(pos), parent(parent)
//{}
//
//PathNode::PathNode(const PathNode& node) : g(node.g), h(node.h), pos(node.pos), parent(node.parent)
//{}
//
//// PathNode -------------------------------------------------------------------------
//// Fills a list (PathList) of all valid adjacent pathnodes
//// ----------------------------------------------------------------------------------
//uint PathNode::FindWalkableAdjacents(PathList& listToFill) const
//{
//	iPoint cell;
//	uint before = listToFill.list.Count();
//
//	// north
//	cell.Create(pos.x, pos.y + 1);
//	if (app->pathfinding->IsWalkable(cell))
//		listToFill.list.Add(PathNode(-1, -1, cell, this));
//
//	// south
//	cell.Create(pos.x, pos.y - 1);
//	if (app->pathfinding->IsWalkable(cell))
//		listToFill.list.Add(PathNode(-1, -1, cell, this));
//
//	// east
//	cell.Create(pos.x + 1, pos.y);
//	if (app->pathfinding->IsWalkable(cell))
//		listToFill.list.Add(PathNode(-1, -1, cell, this));
//
//	// west
//	cell.Create(pos.x - 1, pos.y);
//	if (app->pathfinding->IsWalkable(cell))
//		listToFill.list.Add(PathNode(-1, -1, cell, this));
//
//	return listToFill.list.Count();
//}
//
//// PathNode -------------------------------------------------------------------------
//// Calculates this tile score
//// ----------------------------------------------------------------------------------
//int PathNode::Score() const
//{
//	return g + h;
//}
//
//// PathNode -------------------------------------------------------------------------
//// Calculate the F for a specific destination tile
//// ----------------------------------------------------------------------------------
//int PathNode::CalculateF(const iPoint& destination)
//{
//	g = parent->g + 1;
//	h = pos.DistanceTo(destination);
//
//	return g + h;
//}
//
//// ----------------------------------------------------------------------------------
//// Actual A* algorithm: return number of steps in the creation of the path or -1 ----
//// ----------------------------------------------------------------------------------
//int PathFinding::CreatePath(const iPoint& origin, const iPoint& destination)
//{
//	// L12b: TODO 1: if origin or destination are not walkable, return -1
//
//	// L12b: TODO 2: Create two lists: open, close
//	// Add the origin tile to open
//	// Iterate while we have tile in the open list
//
//	// L12b: TODO 3: Move the lowest score cell from open list to the closed list
//
//	// L12b: TODO 4: If we just added the destination, we are done!
//	// Backtrack to create the final path
//	// Use the Pathnode::parent and Flip() the path when you are finish
//
//	// L12b: TODO 5: Fill a list of all adjancent nodes
//
//	// L12b: TODO 6: Iterate adjancent nodes:
//	// ignore nodes in the closed list
//	// If it is NOT found, calculate its F and add it to the open list
//	// If it is already in the open list, check if it is a better path (compare G)
//	// If it is a better path, Update the parent
//
//	return -1;
//}

int PathFinding::Heuristic(iPoint start, iPoint end)
{
	return abs(start.x - end.x) + abs(start.y - end.y);
}

List<iPoint> Neighbours(iPoint current, int speed)
{
	List<iPoint> list = List<iPoint>();
	// Order is top, right, bottom, left
	list.Add(iPoint(current.x, current.y - speed));
	list.Add(iPoint(current.x + speed, current.y));
	list.Add(iPoint(current.x, current.y - speed));
	list.Add(iPoint(current.x - speed, current.y));

	return list;

}

iPoint PathFinding::NextMove(NodeAstar* endNode, iPoint start)
{
	NodeAstar* current = endNode;

	while (current->GetPreviousNode()->GetPos() != start)
	{
		current = current->GetPreviousNode(); 
	}
	return current->GetPos();
}

bool PathFinding::isVisited(iPoint nodePoint, List<NodeAstar*> visited) 
{
	ListItem<NodeAstar*>* current = visited.At(0);
	while (current != NULL) 
	{
		if (current->data->GetPos() == nodePoint) {
			return true;
		}

		current = current->next;
	}

	return false;
}

priority_queue<NodeAstar*> PathFinding::UpdateNeighbours(priority_queue<NodeAstar*> nodes, 
	iPoint neighbourPoint, int newCost, NodeAstar* curr, NodeAstar* endNode, List<NodeAstar*> visited)
{	int manhattan = Heuristic(neighbourPoint, endNode->GetPos());

	// Create a variable for saving the lost nodes for finding the desired node
	priority_queue<NodeAstar*> save;

	// Taking first value
	NodeAstar* current = nodes.top();
	nodes.pop(); 
	NodeAstar* neighbourNode; 

	//Create a bool for stoping the iteration
	bool foundNode = false; 


	while (current != NULL || foundNode != true)
	{
		// Node in queue
		if (current->GetPos() == neighbourPoint) {
			// If the new calculated cost is lower, change the whole node and push it into the auxiliar queue
			if (current->GetCost() > newCost)
			{
				current->SetCost(newCost);
				current->SetPreviousNode(curr); 
				current->SetPrio(newCost + manhattan);
				save.push(current); 

			}
			else 
			{
				// If the new calculated node is worse, push it to the auxiliar queue without modifying it
				save.push(current); 
			}
			foundNode = true; 
		}
		// Node not in queue
		else 
		{
			// Push the node in the auxiliar queue and find next element in main queue
			save.push(current);
			current = nodes.top();
			nodes.pop(); 
		}

		// Check if the neighbour isn't on the visited list or on the priority queue
		if (isVisited(neighbourPoint, visited) == false || foundNode==false)
		{
			// Create the new node from neighbour
			neighbourNode = new NodeAstar(curr, newCost, neighbourPoint);

			// Calculate it's priority and push it into the priority queue
			int priority = newCost + manhattan;
			neighbourNode->SetPrio(priority); 
			nodes.push(neighbourNode);
		}
	
	return nodes; 
		
	}

	// Iterate over the auxiliar queue and add all it's items on the main queue again. 
	while (save.empty() == false) {
		nodes.push(save.top()); 
		save.pop(); 
	}

}

iPoint PathFinding::Path(iPoint start, int speed)
{
	NodeAstar* startNode = new NodeAstar(nullptr, 0, start);
	int manhattan; 
	std::priority_queue<NodeAstar*> frontier;
	frontier.push(startNode); 

	iPoint end = app->player->playerPos;
	NodeAstar* endNode = new NodeAstar(nullptr, 0, start);

	List<NodeAstar*> visited;
	
	NodeAstar* current = frontier.top(); 

	while (current!=endNode)
	{
		NodeAstar* current = frontier.top();
		frontier.pop(); 
		visited.Add(current);

		if (current->GetPos() == end)
		{
			break;
		}

		List<iPoint> neighbours = Neighbours(current->GetPos(), speed);
		for (int i = 0; i < 4; i++)
		{
			int newCost = current->GetCost() + speed;
			iPoint next = neighbours.At(i)->data;
			frontier = UpdateNeighbours(frontier, neighbours[i], newCost, current, endNode, visited);
		}
	}

	return NextMove(current, start);

}

//CLEANUUUUUUUP
