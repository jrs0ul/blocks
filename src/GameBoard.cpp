#include "GameBoard.h"


void GameBoard::clean(){
    for (unsigned i = 0; i < 22; i++){
        for (unsigned a = 0; a < 10; a++){
            board[i][a] = 0;
        }
    }

}
//--------------------
void GameBoard::draw(PicsContainer& pics){
    for (unsigned i = 0; i < 20; i++){
        for (unsigned a = 0; a < 10; a++){
            if (board[i + 2][a])
                pics.draw(1, 16 + a * 16, 16 + i*16, 1, false, 1.0f, 1.0f, 0.0f, COLOR(1,0,0), COLOR(1,0,0));
        }
    }

}

//---------------------
bool GameBoard::isTopRowDirty(){
    for (int i = 0; i < 10; i++){
        if (board[1][i])
            return true;
    }
    return false;
}
//---------------------
int GameBoard::findLines(){
    int lineCount = 0;
    int blockCounter = 0;
    for (unsigned i = 0; i < 20; i++){
        for (unsigned a = 0; a < 10; a++){
            if (board[i + 2][a])
                blockCounter++;
        }
        if (blockCounter == 10){
            lineCount++;

            for (unsigned z = i + 2; z >= 1; z--){
                for (unsigned b = 0; b < 10; b++){
                    board[z][b] = board[z-1][b];
                }
            }


        }
        blockCounter = 0;
    }

    return lineCount;
}

