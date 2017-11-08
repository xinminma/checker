#include "ListToTree.h"

bool isLoop(int startXY, int s[], int e[]) {
	int k = e[startXY];
	while (k != startXY) {
		//if(s[k] > 0)
		k = e[k];
		if (k == 0) return false;
	}
	return true;
}

void setNewMoveList(int end, int startXY, int eList[], Steps &ns) {
	//ns.print();
	int start = eList[end];
	if (start != startXY)
		setNewMoveList(start, startXY, eList, ns);
	XY s(start), e(end);
	Step step(s, e);
	ns.add(step);
}

bool setNewMoveListAfterLoop(int end, int startXY, int eList[], Steps &ns, int loop_first_node) {
	bool repeat_loop = true;
	int start = eList[end];
	if (start != startXY)
		repeat_loop = setNewMoveListAfterLoop(start, startXY, eList, ns, loop_first_node);

	if (end == loop_first_node)
		repeat_loop = false;
	XY s(start), e(end);
	Step step(s, e);
	ns.add(step);
	return repeat_loop;
}

void setNewLoopMoveList(int end, int startXY, int eList[], Steps &ns) {
	int start = eList[end];
	if (start != startXY)
		setNewLoopMoveList(start, startXY, eList, ns);
	XY s(start), e(end);
	Step step(s, e);
	ns.add(step);
	//gb.doMove(s, e);

}

void ListToTree::setTree(){
	//std::vector<Steps *>

	int startXY;
	//
	// build the start and end array by using steps
	int eList[256] = {};
	int sList[256] = {};
	//1. buil end array
	for (int i = 0; i < _TheSteps.steps.size(); ++i) {
		Step &t = _TheSteps.steps[i];
		XY s = t.start;
		XY e = t.end;
		if (i == 0) startXY = s.toInt();
		//std::cout <<s.toString()<<", "<< e.toString()<< std::endl;
		eList[e.toInt()] = s.toInt();
	}

	XY sxy(startXY);
	std::cout << "\n\nstart:" << sxy.toString() << std::endl;
	std::cout << "------------------" << std::endl;

	// 2. build start array
	for (int i = 0; i < 256; ++i) {
		int idx = eList[i];
		if (idx > 0) {
			sList[idx] = i;
			XY s(idx), e(i);
			//std::cout<<s.toString()<<": "<< e.toString() <<std::endl;
		}
	}


	// 3. create move list without loop steps
	for (int i = 0; i < 256; ++i) {
		if (eList[i] == 0) continue;

		if (sList[i] > 0) continue; //it's a middle node
		//std::cout<< "without Loop: "<<i << std::endl;
		Steps *ns = new Steps();
		setNewMoveList(i, startXY, eList, *ns);
		_TheResultList.push_back(ns);
	}

	// create boards with loop
	//std::cout<< "ns_Loop: " << std::endl;
	Steps ns_loop;
	bool isTheLoop = false;
	for (int i = 0; i < 256; ++i) {
		if (eList[i] == 0) continue;

		if (i == startXY && isLoop(startXY, sList, eList)) {
			isTheLoop = true;
			//std::cout<< "in isLoop: " << i<<std::endl;
			setNewLoopMoveList(i, startXY, eList, ns_loop);
		}
	}
//	std::cout<< "ns_Loop start" <<std::endl;
//	ns_loop.print();
//	std::cout << "ns_Loop end" << std::endl;

	if (isTheLoop) {
		Step loop_start = ns_loop.steps[0]; //don't repeat
		int loop_first_node = loop_start.end.toInt();
		//std::cout << "loop_start:" << loop_start.start.toString() << ", " << loop_start.end.toString() << "; end as int: " << loop_first_node << std::endl;

		for (int i = 0; i < 256; ++i) {
			if (eList[i] == 0) continue;
			if (sList[i] > 0) continue; //it's a middle node
			
			Steps *tns = new Steps(ns_loop);
			//std::cout<<"**** after Loop, before recusive *** "<<std::endl;
			//tns->print();
			bool repeat_loop = setNewMoveListAfterLoop(i, startXY, eList, *tns, loop_first_node);
			//std::cout<<"**** after Loop *** "<<std::endl;
			//tns->print();
			if (repeat_loop)
				_TheResultList.push_back(tns);

		}

	}
}
