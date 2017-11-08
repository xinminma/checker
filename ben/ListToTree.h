#include "GameBoard.h"

#ifndef CHECKERSAI_LISTTOTREE_H
#define CHECKERSAI_LISTTOTREE_H

class ListToTree {
public:
	Steps &_TheSteps;
	std::vector<Steps *> _TheResultList;

	ListToTree(Steps &st) :_TheSteps(st) {}
	void setTree();
};



#endif //CHECKERSAI_LISTTOTREE_H
