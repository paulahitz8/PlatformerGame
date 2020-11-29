#include "App.h"
#include "PathFinding.h"
#include "Player.h"
#include "List.h"
#include <unordered_map>
#include <queue> 

#include "Defs.h"
#include "Log.h"


template<typename T, typename priority_t>
struct PriorityQueue {
	typedef std::pair<priority_t, T> PQElement;
	std::priority_queue<PQElement, std::vector<PQElement>,
		std::greater<PQElement>> elements;

	inline bool empty() const {
		return elements.empty();
	}

	inline void put(T item, priority_t priority) {
		elements.emplace(priority, item);
	}

	T get() {
		T best_item = elements.top().second;
		elements.pop();
		return best_item;
	}
};


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

iPoint PathFinding::NextMove(std::unordered_map<iPoint, iPoint> cameFrom, iPoint end, iPoint start) 
{
	iPoint current = end;

	while (cameFrom[current] != start)
	{
		current = cameFrom[current];
	}
	return current; 
}

iPoint PathFinding::Path(iPoint start, int speed) 
{
	
	PriorityQueue<iPoint, double> frontier;
	std::unordered_map<iPoint, iPoint> came_from; 
	std::unordered_map<iPoint, int> cost_so_far;
	frontier.put(start, 0);
	iPoint end = app->player->playerPos;
	came_from[start] = start;
	cost_so_far[start] = 0;

	while (!frontier.empty()) 
	{
		iPoint current = frontier.get();

		if (current == end)
		{
			break;
		}
		List<iPoint> neighbours = Neighbours(current, speed);
		for (int i = 0; i < 4; i++) 
		{
			double new_cost = cost_so_far[current] + speed;
			iPoint next = neighbours.At(i)->data;
			if (cost_so_far.find(next) == cost_so_far.end() || new_cost < cost_so_far[next]) 
			{
				cost_so_far[next] = new_cost;
				double priority = new_cost + Heuristic(next, end);
				frontier.put(next, priority);
				came_from[next] = current;
			}
		}
	}

	return NextMove(came_from, end, start);

}


