#ifndef NODEASTAR
#define NODEASTAR
#include "Point.h"
class NodeAstar
{
public:

	NodeAstar(NodeAstar*, int, iPoint);
	virtual ~NodeAstar();

	NodeAstar* GetPreviousNode();
	int GetCost();
	iPoint GetPos();
	int GetPrio();

	void SetPreviousNode(NodeAstar*);
	void SetCost(int);
	void SetPos(iPoint);
	void SetPrio(int);

private:

	NodeAstar* cameFrom;
	int costSoFar;
	iPoint nodePos;
	int priority;

};

bool operator<(NodeAstar& a, NodeAstar& b);
bool operator>(NodeAstar& a, NodeAstar& b);
bool operator==(NodeAstar& a, NodeAstar& b);
#endif
