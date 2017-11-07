//
// Created by New on 11/4/2017.
//

#include "Player1.h"


void Player1::getNextJump (XY cc, Composite *jump) {
    //TOP LEFT
    if (cc.x > 0 && cc.y > 0) {
        XY xy(cc.x - 1, cc.y - 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x - 1][xy.y - 1] == 0 && (xy.x > 0 && xy.y > 0)) {
            //ADD JUMP
            XY zz(xy.x - 1, xy.y - 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    //TOP RIGHT
    if (cc.x > 0 && cc.y < 7) {
        XY xy(cc.x - 1, cc.y + 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x - 1][xy.y + 1] == 0 && (xy.x > 0 && xy.y < 7)) {
            //ADD JUMP
            XY zz(xy.x - 1, xy.y + 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    if (!isKing) return;
    //BOTTOM LEFT
    if (cc.x < 7 && cc.y > 0) {
        XY xy(cc.x + 1, cc.y - 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x + 1][xy.y - 1] == 0 && (xy.x < 7 && xy.y > 0)) {
            //ADD JUMP
            XY zz(xy.x + 1, xy.y - 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
    //BOTTOM RIGHT
    if (cc.x < 7 && cc.y < 7) {
        XY xy(cc.x + 1, cc.y + 1);
        int v = parent.board[xy.x][xy.y];
        if ((v == REGULAR || v == KINGVAL) && parent.board[xy.x + 1][xy.y + 1] == 0 && (xy.x < 7 && xy.y < 7)) {
            //ADD JUMP
            XY zz(xy.x + 1, xy.y + 1);
            if (jump == NULL || (possibleMoves.isNotLoop(zz) && cc.equal(jump->origin))) {
                jump = new Composite(true, cc);
                possibleMoves.add(jump);
                isJump = true;
            }
            bool isAdded = jump->add(new Leaf(cc, zz));
            if(isAdded)
                getNextJump(zz, jump);
        }
    }
}

void Player1::getNextMove (XY cc) {
    if(isJump) return;
    //Check Top Left
    if (cc.x > 0 && cc.y > 0) {
        XY xy(cc.x-1, cc.y-1);
        if (parent.board[xy.x][xy.y] == 0) {
            //ADD MOVE
            possibleMoves.add(new Leaf(cc,xy));
        }
    }
    //Check Top Right
    if (cc.x > 0 && cc.y < 7) {
        XY xy(cc.x-1, cc.y+1);
        if (parent.board[xy.x][xy.y] == 0) {
            //ADD MOVE
            possibleMoves.add(new Leaf(cc, xy));
        }
    }
    if(!isKing) return;
    //Check Bottom Left
    if (cc.x < 7 && cc.y > 0) {
        XY xy(cc.x+1, cc.y-1);
        if (parent.board[xy.x][xy.y] == 0) {
            //ADD MOVE
            possibleMoves.add(new Leaf(cc, xy));
        }
    }
    //Check Bottom Right
    if (cc.x < 7 && cc.y < 7) {
        XY xy(cc.x+1, cc.y+1);
        if (parent.board[xy.x][xy.y] == 0) {
            //ADD MOVE
            possibleMoves.add(new Leaf(cc, xy));
        }
    }
}


void Player1::createAllMoves() {
    for (int i = 0; i < parent.number_P1_pieces; i++) {
        XY cc = parent.P1_pieces[i];
        unsigned char temp = parent.board[cc.x][cc.y];
        isKing = temp > 2;
        parent.board[cc.x][cc.y] = 0;
        getNextJump(cc, NULL);
        parent.board[cc.x][cc.y] = temp;
    }
    if(!isJump) {
        for (int i = 0; i < parent.number_P1_pieces; i++) {
            XY cc = parent.P1_pieces[i];
            isKing = parent.board[cc.x][cc.y] > 2;
            getNextMove(cc);
        }
    }
}
Composite *Player1::getOneJumpMoveList(int i) {
    clean();
    XY cc = parent.P1_pieces[i];
    unsigned char temp = parent.board[cc.x][cc.y];
    isKing = temp > 2;
    parent.board[cc.x][cc.y] = 0;
    getNextJump(cc, NULL);
    parent.board[cc.x][cc.y] = temp;
    return &possibleMoves;
}
void Player1::getOneMoveList(int i) {
    XY cc = parent.P1_pieces[i];
    isKing = parent.board[cc.x][cc.y] > 2;
    getNextMove(cc);
}


void Player1::printMoves() {
    possibleMoves.traverse();
}




