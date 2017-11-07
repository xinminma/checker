#include <iostream>

#include "GameBoard.h"
#include "Player1.h"
#include "P1NextBoards.h"

GameBoard *P1NextBoards::getBoard(int idx) {
    GameBoard *pgb = new GameBoard(originalBoard);
    NextSteps *ns = getNextSteps(idx);
    for(int i=0; i<ns->steps.size(); ++i) {
        Step t = ns->steps[i];
        pgb->doMove(t.start, t.end);
    }
    return pgb;
}

void P1NextBoards::setNewGameBoard(int end, int startXY, int eList[], NextSteps &ns) {
    //ns.print();
    int start = eList[end];
    if(start != startXY)
        setNewGameBoard(start, startXY, eList, ns);
    XY s(start), e(end);
    Step step(s, e);
    ns.add(step);
    //gb.doMove(s, e);
}

void P1NextBoards::setNewLoopGameBoard(int end, int startXY, int eList[], NextSteps &ns) {
    int start = eList[end];
    if(start != startXY)
        setNewLoopGameBoard(start, startXY, eList, ns);
    XY s(start), e(end);
    Step step(s, e);
    ns.add(step);
    //gb.doMove(s, e);

}
bool P1NextBoards::isLoop(int startXY, int s[], int e[]) {
    int k = e[startXY];
    while(k != startXY) {
        //if(s[k] > 0)
        k = e[k];
        if(k == 0) return false;
    }
    return true;
}

void P1NextBoards::doMoveP1() {
    Player1 p1(originalBoard);

    //p1.createAllBoards();
    //p1.printMoves();
    std::vector < Component * > leafList;

    for(int i=0; i<p1.parent.number_P1_pieces; ++i) {
        Composite *c = p1.getOneJumpMoveList(i);
        //std::cout<< " *** " <<i<< " *** "<<std::endl;
        //c->traverse();
        c->traverseSet(leafList);
    }

    int l = leafList.size();
    //std::cout<<std::endl <<l<<std::endl;
    //XY startXY;
    int startXY;
//
// build the start and end array
    int eList[256]= {};
    int sList[256]= {};
    for(int i=0; i<leafList.size(); ++i) {
        Leaf *lp = dynamic_cast<Leaf*>(leafList[i]);
        if(lp != NULL) {
            XY s = lp->start;
            XY e = lp->end;
            if(i==0) startXY = s.toInt();
            //std::cout <<s.toString()<<", "<< e.toString()<< std::endl;
            eList[e.toInt()] = s.toInt();
        } else 
            std::cout<<"Null leaf"<<std::endl;
    }

    std::cout<< "------------------"<<std::endl;
    XY sxy(startXY);
    std::cout<< "start:"<<sxy.toString()<<std::endl;

    for(int i=0; i<256; ++i) {
        int idx = eList[i];
        if(idx > 0) {
            sList[idx] = i;
            XY s(i), e(idx);
            std::cout<<s.toString()<<": "<< e.toString() <<std::endl;
        }
    }


// create boards without loop steps
    for(int i=0; i<256; ++i) {
        if(eList[i] == 0) continue;

        if(sList[i] > 0) continue; //it's a middle node
        std::cout<< "without Loop: "<<i << std::endl;
        NextSteps *ns = new NextSteps();
        setNewGameBoard(i, startXY, eList, *ns);
        //add(new GameBoard(oneGb));
        add(ns);
        //ns->print();
        //gameTree.add(new GameBoard(oneGb));
        //oneGb.printBoard();
    }

// create boards with loop
    //GameBoard oneGb(gb);

    std::cout<< "ns_Loop: " << std::endl;
    NextSteps ns_loop;
    bool isTheLoop = false;
     for(int i=0; i<256; ++i) {
        if(eList[i] == 0) continue;

         if(i == startXY && isLoop(startXY, sList, eList)) {
             isTheLoop = true;
             std::cout<< "in isLoop: " << i<<std::endl;
             setNewLoopGameBoard(i, startXY, eList, ns_loop);
             //oneGb.printBoard();
         } 
     }
    //ns_loop.print();

     if(isTheLoop) {
        for(int i=0; i<256; ++i) {
            if(eList[i] == 0) continue;
            if(sList[i] > 0) continue; //it's a middle node
            //GameBoard theOneGb(oneGb);
            NextSteps *tns = new NextSteps(ns_loop);
            //std::cout<<"**** after Loop, before recusive *** "<<std::endl;
            //tns->print();
            setNewGameBoard(i, startXY, eList, *tns);
            //add(new GameBoard(theOneGb));
            //std::cout<<"**** after Loop *** "<<std::endl;
            //tns->print();
            add(tns);

            //theOneGb.printBoard();
        }
     }
}
