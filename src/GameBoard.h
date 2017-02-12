#ifndef _GAME_BOARD
#define _GAME_BOARD
#include "TextureLoader.h"


class GameBoard{
public:

    
    unsigned char board[22][10];
    void clean();
    void draw(PicsContainer& pics);
    bool isTopRowDirty();
    int findLines();

};


#endif //_GAME_BOARD
