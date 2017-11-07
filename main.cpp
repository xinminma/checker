#include <iostream>

#include "GameBoard.h"
#include "Player1.h"
#include "CheckerComposite.h"
#include "P1NextBoards.h"

void initialize(GameBoard &gb) {
    //INITIAL BOARD
    unsigned char initialBoard[8][8] = {
            {0, 2, 0, 2, 0, 2, 0, 2},
            {2, 0, 2, 0, 2, 0, 2, 0},
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {1, 0, 1, 0, 1, 0, 1, 0},
            {0, 1, 0, 1, 0, 1, 0, 1},
            {1, 0, 1, 0, 1, 0, 1, 0}
    };

    // JUMP TEST BOARD
    unsigned char testJumpBoard[8][8] = {
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 1, 0, 0, 0, 2, 0},
            {0, 2, 0, 2, 0, 2, 0, 2},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {1, 0, 1, 0, 3, 0, 1, 0},
            {0, 1, 0, 2, 0, 1, 0, 1},
            {1, 0, 0, 0, 1, 0, 1, 0}
    };
    unsigned char testSquareJumpBoard[8][8] = {
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 3, 0, 0, 0},
            {0, 0, 0, 2, 0, 2, 0, 0},
            {0, 0, 0, 0, 0, 0, 0, 0}
    };
    //gb.setBoard(initialBoard);
    gb.setBoard(testJumpBoard);
    //gb.setBoard(testSquareJumpBoard);
    gb.setPieces();
    gb.setHeuristic();

}

void doTestNextMove(GameBoard &playingboard) {
    Player1 p1(playingboard);
    Player2 p2(playingboard);

    p1.createAllMoves();
    p2.createAllMoves();

    std::cout << std::endl << "== PLAYER 1 MOVES ==";
    p1.printMoves();
    //std::cout << std::endl << "== PLAYER 2 MOVES ==";
    //p2.printMoves();
    //playingboard.flipBoard();
}



int main () {

    GameBoard playingboard;
    initialize(playingboard);
    playingboard.printBoard();

    //doTestNextMove(playingboard);
    //playingboard.printPiece();
    P1NextBoards p1(playingboard);
    p1.doMoveP1();
    std::cout<<"*** all possible boards: " <<p1.size()<<" ***"<<std::endl;
    for(int i=0; i<p1.size(); ++i) {
        GameBoard *gb = p1.getBoard(i);
        gb->printBoard();
    }

    return 0;

}
