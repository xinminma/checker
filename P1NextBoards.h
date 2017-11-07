#ifndef CHECKERSAI_P1NEXTBOARDS_H
#define CHECKERSAI_P1NEXTBOARDS_H

class Step {
public:
    XY start;
    XY end;
    Step(XY startcc, XY endcc) { start = startcc; end = endcc; }
};

class NextSteps {
public:
    NextSteps() {}
    NextSteps(NextSteps &ns) {
        for(int i=0; i<ns.steps.size(); ++i) {
            steps.push_back(ns.steps[i]);
        }
    }
    std::vector<Step > steps;
    void add(Step s) { steps.push_back(s);}
    void print() {
        for(int i=0; i<steps.size(); ++i) {
            Step t = steps[i];
            std::cout<<"loop "<< t.start.toString() <<", " <<t.end.toString()<<std::endl;
        }
    }
};

class P1NextBoards {
    int numberOfMoves;
    NextSteps *nextSteps[4];
    GameBoard &originalBoard;

    void add(NextSteps *p) {
        nextSteps[numberOfMoves++] = p;
    }

    void setNewGameBoard(int end, int startXY, int eList[], NextSteps &ns);
    void setNewLoopGameBoard(int end, int startXY, int eList[], NextSteps &ns);
    bool isLoop(int startXY, int s[], int e[]);
public:
    P1NextBoards(GameBoard &gb):numberOfMoves(0),originalBoard(gb) { }
    ~P1NextBoards() {
        //delete[] nextSteps;
    }
    void doMoveP1(int index); //index is the piece location
    int size() { return numberOfMoves; }
    NextSteps *getNextSteps(int i) { return nextSteps[i]; }

    GameBoard *getBoard(int i);
	void clean() {
		//delete[] nextSteps;
		numberOfMoves = 0;
	}
};


#endif //CHECKERSAI_P1NEXTBOARDS_H
