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
