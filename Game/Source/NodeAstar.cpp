#include "NodeAstar.h"
#include "App.h"

bool operator<(NodeAstar& a, NodeAstar& b) 
{
	return a.GetPrio() < b.GetPrio(); 
}
bool operator>(NodeAstar& a, NodeAstar& b)
{
	return a.GetPrio() > b.GetPrio();
}
bool operator==(NodeAstar& a, NodeAstar& b)
{
	return a.GetPos() == b.GetPos();
}

NodeAstar::NodeAstar(NodeAstar* prevNode, int cost, iPoint position)
{
	cameFrom = prevNode;
	costSoFar = cost;
	nodePos = position;
}

NodeAstar::~NodeAstar() {}

NodeAstar* NodeAstar::GetPreviousNode()
{
	return cameFrom;
}

int NodeAstar::GetCost()
{
	return costSoFar;
}

iPoint NodeAstar::GetPos()
{
	return nodePos;
}

int NodeAstar::GetPrio()
{
	return priority;
}

void NodeAstar::SetPreviousNode(NodeAstar* newNode)
{
	cameFrom = newNode;
}

void NodeAstar::SetCost(int newCost)
{
	costSoFar = newCost;
}

void NodeAstar::SetPos(iPoint newPos)
{
	nodePos = newPos;
}

void NodeAstar::SetPrio(int newPrio)
{
	priority = newPrio;
}