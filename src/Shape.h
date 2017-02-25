#ifndef _SHAPE_H
#define _SHAPE_H
#include "GameBoard.h"
#include "TextureLoader.h"


#define MAXTICKS 20
#define MAXSHAPES 7

const unsigned char shapeData[7][16] = {{1, 1, 0, 0,
                                         1, 1},

                                        {0, 1, 0, 0,
                                         1, 1, 1, 0},

                                        {0, 1, 1, 0,
                                         1, 1, 0, 0},

                                        {1, 1, 0, 0,
                                         0, 1, 1, 0},

                                        {1, 1, 1, 0,
                                         0, 0, 1, 0},

                                        {1, 1, 1, 0,
                                         1, 0, 0, 0},
                                        
                                        {1, 1, 1, 1}};

class Shape{

    unsigned char data[16];
    int timer;
    int deathTimer;
    COLOR c;
    unsigned state;
public:
    unsigned int x;
    unsigned int y;
    int lag;

    unsigned type;

    unsigned int width;
    unsigned int height;
    bool dead;


    bool overlaps(GameBoard& b, int shiftX, int shiftY);
    void moveLeft(GameBoard& b);
    void moveRight(GameBoard& b);
    void moveDown(GameBoard& b);
    void stay(GameBoard& b);
    void draw(unsigned int px, unsigned int py, PicsContainer& pics);
    void rotate(GameBoard& b);
    void speedUp(){timer = lag;}

    Shape(const Shape& s){
        //printf("copying shape\n");
        memcpy(data, s.data, 16);
        width = s.width;
        height = s.height;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        lag = MAXTICKS;
        deathTimer = 0;
        c = s.c;
        type = s.type;
        state = 0;
    }
//-------------
    Shape(int t){

        switch(t){
            case 0:{
                memcpy(data, shapeData[0], 16);
                width = 2;
                height = 2;
                c = COLOR(0, 0, 1);
            }break;
            case 1:{
                memcpy(data, shapeData[1], 16);
                width = 3;
                height = 2;
                c = COLOR(1, 1, 0);
            }break;

             case 2:{
                memcpy(data, shapeData[2], 16);
                width = 3;
                height = 2;
                c = COLOR(1, 0, 0.5f);

            }break;
            case 3:{
                memcpy(data, shapeData[3], 16);

                width = 3;
                height = 2;
                c = COLOR(0, 1, 0);

            }break;

            case 4:{
                memcpy(data, shapeData[4], 16);

                width = 3;
                height = 2;
                c = COLOR(0, 1, 1);
            }break;

            case 5:{
                memcpy(data, shapeData[5], 16);
                width = 3;
                height = 2;
                c = COLOR(1, 0.5f, 0);
            }break;

            case 6:{
                memcpy(data, shapeData[6], 16);
                width = 4;
                height = 1;
                c = COLOR(1, 0, 0);
            }break;

        }
        lag = MAXTICKS;
        x = 5;
        y = 0;
        dead = false;
        timer = 0;
        deathTimer = 0;
        type = t;
        state = 0;

    }

};



#endif //_SHAPE_H
